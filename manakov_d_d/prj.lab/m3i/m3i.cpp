#include <cstring>
#include <iostream>
#include <m3i/m3i.h>
#include <stdexcept>

inline int min(const int a, const int b) { return (a < b) ? a : b; }

typedef const std::lock_guard<std::mutex> lock_guard;

M3i::M3i() = default;

// {{{123}, {123}}, {{123}, {123}}, {{123}, {123}}, ...}
M3i::M3i(
    std::initializer_list<std::initializer_list<std::initializer_list<int>>>
        ilist) {
  tensor = new Tensor();
  tensor->shape[0] = ilist.size();
  tensor->shape[1] = ilist.begin()->size();
  tensor->shape[2] = ilist.begin()->begin()->size();
  tensor->capacity = tensor->shape[0] * tensor->shape[1] * tensor->shape[2];
  tensor->data = new int[tensor->capacity];

  int dumb_iter = 0;
  for (auto &sublist : ilist) {
    for (auto &subsublist : sublist) {
      for (auto &value : subsublist) {
        tensor->data[dumb_iter++] = value;
      }
    }
  }
}

M3i::M3i(int d0, int d1, int d2) {
  tensor = new Tensor();
  tensor->shape[0] = d0;
  tensor->shape[1] = d1;
  tensor->shape[2] = d2;
  tensor->capacity = d0 * d1 * d2;
  CheckDims();
  tensor->data = new int[tensor->capacity];
}

M3i::M3i(int d0, int d1, int d2, int fill) {
  tensor = new Tensor();
  tensor->shape[0] = d0;
  tensor->shape[1] = d1;
  tensor->shape[2] = d2;
  tensor->capacity = d0 * d1 * d2;
  CheckDims();
  tensor->data = new int[tensor->capacity]();

  for (int i = 0; i < tensor->capacity; ++i)
    tensor->data[i] = fill;
}

// легкая копия(подсчет ссылок)
M3i::M3i(const M3i &other) : tensor(other.tensor) { ++tensor->ref_counter; }

// легкая копия(подсчет ссылок)
M3i &M3i::operator=(const M3i &other) {
  free();
  tensor = other.tensor;
  ++tensor->ref_counter;
  return *this;
}

M3i::M3i(M3i &&other) : tensor(other.tensor) { other.tensor = nullptr; }

M3i &M3i::operator=(M3i &&other) {
  if (this == &other) {
    return *this;
  }

  free();
  tensor = other.tensor;
  other.tensor = nullptr;
  return *this;
}

M3i::~M3i() { free(); }

// полная копия данных
M3i M3i::Clone() const {
  lock_guard(tensor->mutex);
  M3i ret(tensor->shape[0], tensor->shape[1], tensor->shape[2]);

  memcpy(ret.tensor->data, tensor->data, tensor->capacity);
  return ret;
}

// except: хотя бы один из индексов меньше нуля или больше
// соответствующей размерности
M3i &M3i::Resize(int d0, int d1, int d2) {
  CheckDims(d0, d1, d2);
  lock_guard(tensor->mutex);
  int *buffer = new int[d0 * d1 * d2]();

  for (int i = 0; i < min(tensor->shape[0], d0); ++i) {
    for (int j = 0; j < min(tensor->shape[1], d1); ++j) {
      for (int k = 0; k < min(tensor->shape[2], d2); ++k) {
        buffer[i * d1 * d2 + j * d2 + k] = this->At(i, j, k);
      }
    }
  }

  delete[] tensor->data;
  tensor->shape[0] = d0;
  tensor->shape[1] = d1;
  tensor->shape[2] = d2;
  tensor->capacity = d0 * d1 * d2;
  tensor->data = buffer;

  return *this;
}

// except: хотя бы один из индексов меньше нуля или больше
// соответствующей размерности
int &M3i::At(int i, int j, int k) {
  CheckIndexes(i, j, k);
  return tensor->data[i * tensor->shape[1] * tensor->shape[2] +
                      j * tensor->shape[2] + k];
}

// except: хотя бы один из индексов меньше нуля или больше
// соответствующей размерности
int M3i::At(int i, int j, int k) const {
  CheckIndexes(i, j, k);
  return tensor->data[i * tensor->shape[1] * tensor->shape[2] +
                      j * tensor->shape[2] + k];
}

// получение размера по измерению 0, 1, 2
// except: dim < 0 or dim > 2
int M3i::Size(int dim) const {
  if (dim < 0 || dim > 2) {
    throw std::invalid_argument("dim must be between 0 and 2");
  }
  return tensor->shape[dim];
}

// заполнение одним и тем же значением
void M3i::Fill(int val) {
  lock_guard(tensor->mutex);
  for (int i = 0; i < tensor->capacity; ++i)
    tensor->data[i] = val;
}

std::ostream &M3i::WriteTo(std::ostream &out) const {
  lock_guard(tensor->mutex);

  out << "size: " << tensor->shape[0] << " " << tensor->shape[1] << " "
      << tensor->shape[2] << std::endl;
  for (int i = 0; i < tensor->shape[0]; ++i) {
    for (int j = 0; j < tensor->shape[1]; ++j) {
      for (int k = 0; k < tensor->shape[2]; ++k) {
        out << this->At(i, j, k) << " ";
      }
      out << std::endl;
    }
    out << std::endl;
  }
  return out;
}

std::istream &M3i::ReadFrom(std::istream &in) {
  if (tensor != nullptr) {
    lock_guard(tensor->mutex);
    free();
  }

  std::string must_be_size_string;
  in >> must_be_size_string;
  if (must_be_size_string != "size:") {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  int dims[3];
  in >> dims[0] >> dims[1] >> dims[2];

  if (dims[0] <= 0 || dims[1] <= 0 || dims[2] <= 0) {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  M3i new_me = M3i(dims[0], dims[1], dims[2]);

  for (int i = 0; i < dims[0]; ++i) {
    for (int j = 0; j < dims[1]; ++j) {
      for (int k = 0; k < dims[2]; ++k) {
        in >> new_me.tensor->data[i * dims[1] * dims[2] + j * dims[2] + k];
      }
    }
  }

  *this = new_me;

  return in;
}

std::istream &operator>>(std::istream &in, M3i &m) { return m.ReadFrom(in); }

std::ostream &operator<<(std::ostream &out, const M3i &m) {
  return m.WriteTo(out);
}

void M3i::CheckDims() {
  if (tensor->shape[0] <= 0 || tensor->shape[1] <= 0 || tensor->shape[2] <= 0) {
    throw std::invalid_argument("dimensions must be above zero");
  }
}

void M3i::CheckDims(int d0, int d1, int d2) const {
  if (d0 <= 0 || d1 <= 0 || d2 <= 0) {
    throw std::invalid_argument("dimensions must be above zero");
  }
}

void M3i::CheckIndexes(int d0, int d1, int d2) const {
  if (d0 < 0 || d1 < 0 || d2 < 0 || tensor->shape[0] <= d0 or
      tensor->shape[1] <= d1 || tensor->shape[2] <= d2) {
    throw std::out_of_range("index(es) out of range");
  }
}

void M3i::free() {
  if (tensor == nullptr)
    return;

  lock_guard(tensor->mutex);

  if (--tensor->ref_counter == 0) {
    delete[] tensor->data;
    delete tensor;
  }

  tensor = nullptr;
}

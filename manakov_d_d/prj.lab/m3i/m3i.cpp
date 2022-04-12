#include <cassert>
#include <m3i/m3i.h>
#include <stdexcept>
#include <utility>

inline void unimplemented() { assert(false); }

M3i::M3i() = default;

M3i::M3i(int d0, int d1, int d2)
    : data(new int[d0 * d1 * d2]), dim0(d0), dim1(d1), dim2(d2),
      ref_counter(new int(1)) {
  Fill(0);
}

M3i::M3i(const M3i &other) {
  if (data != nullptr) {
    delete[] data;
    delete ref_counter;
  }

  data = other.data;
  ref_counter = other.ref_counter;
  dim0 = other.dim0;
  dim1 = other.dim1;
  dim2 = other.dim2;
}

M3i::M3i(M3i &&other) {
  if (data != nullptr) {
    delete[] data;
    delete ref_counter;
  }

  data = std::move(other.data);
  ref_counter = std::move(other.ref_counter);
  dim0 = std::move(other.dim0);
  dim1 = std::move(other.dim1);
  dim2 = std::move(other.dim2);
}

M3i &M3i::operator=(M3i &&other) {
  *this = std::move(other);
  return *this;
}

M3i::~M3i() {
  if (data != nullptr && *ref_counter == 1) {
    delete[] data;
    delete ref_counter;
  }
}

const M3i M3i::Clone() const {
  M3i ret(dim0, dim1, dim2);
  for (int i = 0; i < dim0 * dim1 * dim2; ++i) {
    ret.data[i] = data[i];
  }

  return ret;
}

M3i &M3i::Resize(int d0, int d1, int d2) {
  unimplemented();
  throw 0;
}

int &M3i::At(int i, int j, int k) {
  if (i >= dim0 || j >= dim1 || k >= dim2) {
    throw std::out_of_range("out of range");
  }

  return data[i * (dim1 * dim2) + j * dim2 + k];
}

int M3i::At(int i, int j, int k) const {
  if (i >= dim0 || j >= dim1 || k >= dim2) {
    throw std::out_of_range("out of range");
  }

  return data[i * (dim1 * dim2) + j * dim2 + k];
}

int M3i::Size(int dim) const {
  if (dim < 1 || dim > 3) {
    throw std::out_of_range("out of range");
  }

  if (dim == 1) {
    return dim0;
  } else if (dim == 2) {
    return dim1;
  }
  return dim2;
}

void M3i::Fill(int value) {
  for (int i = 0; i < dim0 * dim1 * dim2; ++i) {
    data[i] = value;
  }
}

/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

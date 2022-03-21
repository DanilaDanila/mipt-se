#ifndef M3I_H
#define M3I_H

class M3i {
 public:
  M3i();
  ~M3i();

  M3i(const int size_dim0, const int size_dim1, const int size_dim2);

  // M3i(std::initializer_list)

  M3i(const M3i&);  // light copy (ref count)

  M3i(M3i&&);

  M3i& operator=(const M3i&);  // light copy (ref count)

  M3i& operator=(M3i&&);

  M3i clone() const;  // deep copy

  int& operator[](const int i, const int j, const int k);
  int operator[](const int i, const int j, const int k) const;

  int& at(const int i, const int j, const int k);

  int at(const int i, const int j, const int k) const;

  int size(const int dim);  // tensor.shape[dim]

  void fill(const int val);

 private:
  int* data;
  int ref_counter;
};

std::istream& operator>>(std::istream& in, M3i& m3i);

std::ostream& operator<<(std::ostream& out, const M3i& m3i);

#endif  // M3I_H
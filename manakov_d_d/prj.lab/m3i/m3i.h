#ifndef M3I_H
#define M3I_H

#include <iosfwd>

class M3i {
public:
  M3i();
  M3i(int d1, int d2, int d3);
  // легкая копия(подсчет ссылок)
  M3i(const M3i &other);
  // легкая копия(подсчет ссылок)
  M3i &operator=(const M3i &other);

  M3i(M3i &&other);
  M3i &operator=(M3i &&other);

  ~M3i();

  // полная копия данных
  const M3i Clone() const;

  M3i &Resize(int d1, int d2, int d3);

  // доступ к элементу
  int &At(int i, int j, int k);
  int At(int i, int j, int k) const;

  // получение размера по измерению 0, 1, 2
  int Size(int dim) const;
  // заполнение значениями
  void Fill(int val);

  std::ostream &WriteTo(std::ostream &ostrm) const;
  std::istream &ReadFrom(std::istream &istrm);

private:
  int dim0;
  int dim1;
  int dim2;

  int *data;
  int *ref_counter;
};

std::istream &operator>>(std::istream &istrm, M3i &m);
std::ostream &operator<<(std::ostream &ostrm, const M3i &m);

#endif // M3I_H

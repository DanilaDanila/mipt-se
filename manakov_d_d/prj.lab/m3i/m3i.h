#ifndef M3I_H
#define M3I_H

#include <atomic>
#include <initializer_list>
#include <iosfwd>
#include <memory>
#include <mutex>

class M3i {
public:
  M3i();

  // {{{123}, {123}}, {{123}, {123}}, {{123}, {123}}, ...}
  M3i(std::initializer_list<std::initializer_list<std::initializer_list<int>>>);

  // except: хотя бы один из индексов меньше нуля
  M3i(int d0, int d1, int d2); // незаполняющий конструктор
  M3i(int d0, int d1, int d2, int fill_with); // заполняющий конструктор

  // легкая копия(подсчет ссылок)
  M3i(const M3i &other);

  // легкая копия(подсчет ссылок)
  M3i &operator=(const M3i &other);

  M3i(M3i &&other);
  M3i &operator=(M3i &&other);

  ~M3i();

  // полная копия данных
  M3i Clone() const;

  // except: хотя бы один из индексов меньше нуля или больше
  // соответствующей размерности
  M3i &Resize(int d0, int d1, int d2);

  // except: хотя бы один из индексов меньше нуля или больше
  // соответствующей размерности
  int &At(int i, int j, int k);

  // except: хотя бы один из индексов меньше нуля или больше
  // соответствующей размерности
  int At(int i, int j, int k) const;

  // получение размера по измерению 0, 1, 2
  // except: dim < 0 or dim > 2
  int Size(int dim) const;

  // заполнение одним и тем же значением
  void Fill(int val);

  std::ostream &WriteTo(std::ostream &) const;
  std::istream &ReadFrom(std::istream &);

private:
  void CheckDims();

  void CheckDims(int d0, int d1, int d2) const;

  void CheckIndexes(int i, int j, int k) const;

  void free();

  struct Tensor {
    int shape[3] = {0};
    int capacity = 0;
    int *data = nullptr;
    std::mutex mutex;
    std::atomic_int16_t ref_counter = 1;
  } *tensor = nullptr;
};

std::istream &operator>>(std::istream &, M3i &);

std::ostream &operator<<(std::ostream &, const M3i &);

#endif // M3I_H

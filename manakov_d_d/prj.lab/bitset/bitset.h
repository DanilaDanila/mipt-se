#ifndef BIT_SET_H
#define BIT_SET_H

#include <cstdint>
#include <iosfwd>
#include <vector>

class BitSet {
private:
  class BitHolder;

public:
  BitSet();
  BitSet(int length, bool default_value = false);

  BitSet(const BitSet &);
  BitSet(BitSet &&);

  BitSet &operator=(const BitSet &);
  BitSet &operator=(BitSet &&);

  ~BitSet();

  BitSet &operator|=(const BitSet &other);
  BitSet &operator^=(const BitSet &other);
  BitSet &operator&=(const BitSet &other);
  const BitSet operator~() const;

  int Size() const;
  void Resize(int new_size);
  void Fill(bool value);

  BitHolder operator[](int idx);
  bool operator[](int idx) const;

  BitHolder At(int idx);
  bool At(int idx) const;

private:
  // можно будет вернуть, нельзя создавать
  // auto smth = bset[123];  // compiles
  class BitHolder {
  public:
    BitHolder() = delete;
    BitHolder(uint16_t *byte, uint16_t shift);

    BitHolder(const BitHolder &) = delete;
    BitHolder(BitHolder &&);

    BitHolder &operator=(const BitHolder &);
    BitHolder &operator=(bool);
    BitHolder &operator=(BitHolder &&) = delete;

    explicit operator bool() const;

  private:
    uint16_t *holder;
    uint16_t mask;
  };

  struct SizeMissmatch {};

  int size;
  std::vector<uint16_t> data;
};
const BitSet operator|(const BitSet &first, const BitSet &second);
const BitSet operator&(const BitSet &first, const BitSet &second);
const BitSet operator^(const BitSet &first, const BitSet &second);

#endif // BIT_SET_H

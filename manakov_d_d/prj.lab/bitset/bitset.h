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
  // except: length <= 0
  BitSet(const int length, const bool default_value = false);

  BitSet(const BitSet &);
  BitSet(BitSet &&);

  BitSet &operator=(const BitSet &);
  BitSet &operator=(BitSet &&);

  ~BitSet();

  // except: this->size != other.size
  BitSet &operator|=(const BitSet &other);
  // except: this->size != other.size
  BitSet &operator^=(const BitSet &other);
  // except: this->size != other.size
  BitSet &operator&=(const BitSet &other);
  const BitSet operator~() const;

  int Size() const;

  // except: length <= 0
  void Resize(const int new_size);
  void Fill(const bool value);

  // except: idx < 0 or idx >= size
  BitHolder operator[](const int idx);
  // except: idx < 0 or idx >= size
  bool operator[](const int idx) const;

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
    BitHolder &operator=(BitHolder &&);

    explicit operator bool() const;

  private:
    uint16_t *holder;
    uint16_t mask;
  };

  struct SizeMissmatch {};

  int size;
  std::vector<uint16_t> data;
};
// except: first.size != second.size
const BitSet operator|(const BitSet &first, const BitSet &second);
// except: first.size != second.size
const BitSet operator&(const BitSet &first, const BitSet &second);
// except: first.size != second.size
const BitSet operator^(const BitSet &first, const BitSet &second);

std::istream &operator>>(std::istream &in, BitSet &bs);
std::ostream &operator<<(std::ostream &out, const BitSet &bs);

#endif // BIT_SET_H

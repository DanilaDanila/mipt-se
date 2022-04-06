#include <bitset/bitset.h>
#include <iostream>

BitSet::BitSet() : BitSet(0) {}

BitSet::BitSet(int length, bool default_value)
    : size(length),
      data((length + 15) / 16, uint16_t(0x0) - uint16_t(default_value)) {}

BitSet::BitSet(const BitSet &) = default;
BitSet::BitSet(BitSet &&) = default;

BitSet &BitSet::operator=(const BitSet &) = default;
BitSet &BitSet::operator=(BitSet &&) = default;

BitSet::~BitSet() {}

BitSet &BitSet::operator|=(const BitSet &other) {
  if (Size() != other.Size()) {
    throw SizeMissmatch();
  }

  for (int i = 0; i < data.size(); ++i) {
    data[i] |= other.data[i];
  }

  return *this;
}

BitSet &BitSet::operator^=(const BitSet &other) {
  if (Size() != other.Size()) {
    throw SizeMissmatch();
  }

  for (int i = 0; i < data.size(); ++i) {
    data[i] ^= other.data[i];
  }

  return *this;
}

BitSet &BitSet::operator&=(const BitSet &other) {
  if (Size() != other.Size()) {
    throw SizeMissmatch();
  }

  for (int i = 0; i < data.size(); ++i) {
    data[i] &= other.data[i];
  }

  return *this;
}

int BitSet::Size() const { return size; }

void BitSet::Resize(int size) {
  this->size = size;
  const int vec_size = (size + 15) / 16;
  return data.resize(vec_size);
}

void BitSet::Fill(bool value) {
  const uint16_t pattern = uint16_t(0x0) - uint16_t(value);

  for (auto &block : data) {
    block = pattern;
  }
}

BitSet::BitHolder BitSet::operator[](int idx) {
  uint16_t *ptr = &(*(data.begin() + (idx / 16)));
  /* Внимание!!!
   * Вот именно вот тут (в return) и нужен BitHolder(BitHolder &&)
   */
  return BitHolder(ptr, idx % 16);
}

bool BitSet::operator[](int idx) const {
  // семь бед - один ответ ...
  BitHolder bh = (*const_cast<BitSet *>(this))[idx];
  return static_cast<bool>(bh);
}

BitSet::BitHolder BitSet::At(int idx) {
  if (idx > size) {
    throw std::out_of_range("idx out of range");
  }

  uint16_t *ptr = &(*(data.begin() + (idx / 16)));
  /* Внимание!!!
   * Вот именно вот тут (в return) опять нужен BitHolder(BitHolder &&)
   */
  return BitHolder(ptr, idx % 16);
}

bool BitSet::At(int idx) const {
  BitHolder bh = (*const_cast<BitSet *>(this))[idx];
  return static_cast<bool>(bh);
}

BitSet::BitHolder::BitHolder(uint16_t *byte, uint16_t shift)
    : holder(byte), mask(0x8000 >> shift) {}

BitSet::BitHolder &BitSet::BitHolder::operator=(const BitHolder &other) {
  *holder |= mask & (*other.holder & other.mask);
  return *this;
}

BitSet::BitHolder &BitSet::BitHolder::operator=(bool value) {
  if (value) {
    *holder |= mask;
  } else {
    *holder &= ~mask;
  }
  return *this;
}

BitSet::BitHolder::operator bool() const { return (*holder & mask) != 0x0; }

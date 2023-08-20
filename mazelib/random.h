#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>

namespace {

int GenRandCond(int left, int right) {
  static std::mt19937 rng(std::random_device{}());
  static std::uniform_int_distribution<int> distribution(left, right);
  return distribution(rng);
}

} // namespace

#endif // RANDOM_H_

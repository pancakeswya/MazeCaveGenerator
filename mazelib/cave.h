#ifndef CAVE_H_
#define CAVE_H_

#include "matrix.h"

namespace mcg {

class Cave : public Matrix<int> {
 public:
  bool ReadFile(std::string_view path);
  void Generate(size_t rows, size_t cols);
};

} // namespace maze

#endif // CAVE_H_
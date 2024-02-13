/**
 * @file io.hpp
 * @author Mikhail Lozhnikov
 *
 * Перегруженные операторы для вывода структур данных в поток.
 */

#ifndef TESTS_IO_HPP_
#define TESTS_IO_HPP_

#include <ostream>
#include <vector>

template<typename ElemType>
std::ostream& operator<<(std::ostream& out, const std::vector<ElemType>& vec) {
  if (vec.empty()) {
    out << "[ ]";
    return out;
  }

  out << "[ " << vec[0];

  for (size_t i = 1; i < vec.size(); i++)
    out << ", " << vec[i];

  out << " ]";

  return out;
}

#endif  // TESTS_IO_HPP_

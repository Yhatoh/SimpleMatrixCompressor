#include <set>
#include <utility>

#include "SimpleMatrixCompressor.hpp"
#include "../util/utils.hpp"

namespace matcomp {

template< uint64_t b >
simple_matrix<b>::simple_matrix(std::vector< std::vector< uint64_t > > matrix) {
  n = matrix.size();
  m = matrix[0].size();

  uint64_t blocks = (m + b - 1) / b;
  std::vector< std::set< uint64_t > > uniques(blocks);

  for(uint64_t col = 0; col < m; col++) {
    uint64_t block = col / b;
    for(uint64_t row = 0; row < n; row++) {
      uniques[block].insert(matrix[row][col]);
    }
  }

  uint8_t max_bits = 0;
  for(auto &unique : uniques) {
    max_bits = std::max(max_bits, (uint8_t) ceil_log2(unique.size()));
  }

  // this should be okey
  codebook.assign(blocks, std::vector< uint32_t >(max_bits));

  // this could be improved, i think (maybe)
  for(uint64_t block = 0; block < uniques.size(); block++) {
    std::map< uint64_t, uint64_t > elems_codes = create_codes(uniques[block]);
    for(std::pair< uint64_t, uint64_t > elem_code : elems_codes) {
      uint64_t elem = elem_code.first;
      uint64_t code = elem_code.second;
      codebook[block][code] = elem;
    }
  }

  compressed_matrix.assign(n * m * max_bits / 64, 0);

  for(uint64_t block = 0; block < blocks; block++) {
    for(uint64_t col = block; col < block * b; col++) {
      for(uint64_t row = 0; row < n; row++) {
        uniques[block].insert(matrix[row][col]);
      }
    }
  }
}

template< uint64_t b >
std::map< uint64_t, uint64_t > simple_matrix<b>::create_codes(std::set< uint64_t > nums) {}

template< uint64_t b >
uint64_t simple_matrix<b>::size_in_bits() {}

template< uint64_t b >
uint64_t simple_matrix<b>::size_in_bytes() {}

template< uint64_t b >
uint64_t simple_matrix<b>::get(uint64_t i, uint64_t j) {}

template< uint64_t b >
std::vector< uint64_t > simple_matrix<b>::r_mul(std::vector< uint64_t > x) {}

template< uint64_t b >
std::vector< uint64_t > simple_matrix<b>::l_mul(std::vector< uint64_t > x) {}
}

#include <cstdint>
#include <set>
#include <map>
#include <vector>

namespace matcomp {

template< uint64_t b >
class simple_matrix {
  private:
    uint64_t n, m; // row x column
    uint8_t bits;
    std::vector< uint64_t > compressed_matrix;
    std::vector< std::vector< uint32_t > > codebook;

    std::map< uint64_t, uint64_t > create_codes(std::set< uint64_t > nums);
  public:
    simple_matrix(std::vector< std::vector< uint64_t > > matrix);
    uint64_t size_in_bits();
    uint64_t size_in_bytes();
    uint64_t get(uint64_t i, uint64_t j);
    std::vector< uint64_t > r_mul(std::vector< uint64_t > x);
    std::vector< uint64_t > l_mul(std::vector< uint64_t > x);
};

}

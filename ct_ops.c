#include <stdint.h>
#include <stdio.h>

uint64_t FStar_UInt64_eq_mask(uint64_t a, uint64_t b)
{
  uint64_t x = a ^ b;
  uint64_t minus_x = ~x + (uint64_t)1U;
  uint64_t x_or_minus_x = x | minus_x;
  uint64_t xnx = x_or_minus_x >> (uint32_t)63U;
  return xnx - (uint64_t)1U;
}

uint64_t FStar_UInt64_gte_mask(uint64_t a, uint64_t b)
{
  uint64_t x = a;
  uint64_t y = b;
  uint64_t x_xor_y = x ^ y;
  uint64_t x_sub_y = x - y;
  uint64_t x_sub_y_xor_y = x_sub_y ^ y;
  uint64_t q = x_xor_y | x_sub_y_xor_y;
  uint64_t x_xor_q = x ^ q;
  uint64_t x_xor_q_ = x_xor_q >> (uint32_t)63U;
  return x_xor_q_ - (uint64_t)1U;
}

uint64_t eq_ref(uint64_t a, uint64_t b)
{
    if (a == b) {
        return 0xffffffffffffffff;
    } else {
        return 0;
    }
}

uint64_t gte_ref(uint64_t a, uint64_t b)
{
    if (a >= b) {
        return 0xffffffffffffffff;
    } else {
        return 0;
    }
}

int main() {
    uint64_t a = 0;
    uint64_t b = 0;
    uint64_t r1 = FStar_UInt64_eq_mask(a, b);
    uint64_t r2 = eq_ref(a, b);
    printf("kremlin: %lu == %lu: %lx\n", a, b, r1);
    printf("ref:     %lu == %lu: %lx\n", a, b, r2);

    r1 = FStar_UInt64_gte_mask(a, b);
    r2 = gte_ref(a, b);
    printf("kremlin: %lu > %lu: %lx\n", a, b, r1);
    printf("ref:     %lu > %lu: %lx\n", a, b, r2);
}

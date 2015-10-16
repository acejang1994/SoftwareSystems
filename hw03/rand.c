/*

    Copyright 2007 Allen B. Downey

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    The GNU General Public License is available from
    http://www.gnu.org/licenses/.

*/

#include <inttypes.h>

// generate a random float using the algorithm described
// at allendowney.com/research/rand
float my_random_float()
{
  int x, exp, mant;
  float f;

  // this union is for assembling the float.
  union {
    float f;
    int i;
  } b;

  // generate 31 random bits (assuming that RAND_MAX is 2^31 - 1
  x = random();

  // use bit-sca-forward to find the first set bit and
  // compute the exponent
  asm ("bsfl %1, %0"
       :"=r"(exp)
       :"r"(x)
      );
  exp = 126 - exp;

  // use the other 23 bits for the mantissa (for small numbers
  // this means we are re-using some bits)
  mant = x >> 8;
  b.i = (exp << 23) | mant;

  return b.f;
}

// alternative implementation of my algorithm that doesn't use
// embedded assembly
float my_random_float2()
{
  int x;
  int mant;
  int exp = 126;
  int mask = 1;

  union {
    float f;
    int i;
  } b;

  // generate random bits until we see the first set bit
  while (1) {
    x = random();
    if (x == 0) {
      exp -= 31;
    } else {
      break;
    }
  }

  // find the location of the first set bit and compute the exponent
  while (x & mask) {
    mask <<= 1;
    exp--;
  }

  // use the remaining bit as the mantissa
  mant = x >> 8;
  b.i = (exp << 23) | mant;

  return b.f;
}

/* BOX: this union is used to access the bits
of floating-point values */
typedef union box {
  double d;
  uint64_t i;
} Box;

/* GET_BIT: returns a random bit. For efficiency,
bits are generated 31 at a time using the
C library function random () */
int get_bit () {
  int bit;
  static bits = 0;
  static x;
  if (bits == 0) {
    x = random();
    bits = 31;
  }
  bit = x & 1;
  x = x >> 1;
  bits--;
  return bit;
}

// compute a random double using my algorithm
double my_random_double()
{
  // TODO: fill this in
  uint64_t x;
  uint64_t mant, exp, high_exp, low_exp;
  Box low, high, answer;
  low.d = 0.0;
  high.d = 1.0;

  /* extract the exponent fields from low and high */
  low_exp = (low.i >> 52);
  high_exp = (high.i >> 52);

  /* choose random bits and decrement exp until a 1 appears.
  the reason for subracting one from high_exp is left
  as an exercise for the reader */
  for (exp = high_exp-1; exp > low_exp; exp--) {
    if (get_bit()) break;
  }
  /* choose a random 52-bit mantissa */
  uint64_t rand1 = random();
  uint64_t rand2 = random();

  mant = ((rand1 & 0xFFFFFFF) << 26) | (rand2 & 0xFFFFFFF);

  // printf("%" PRIx64 " mant \n", mant);
  /* if the mantissa is zero, half the time we should move
  to the next exponent range */
  if (mant == 0 && get_bit()) exp++;
  /* combine the exponent and the mantissa */
  answer.i = (exp << 52) | mant;
  return answer.d/2;
}

// return a constant (this is a dummy function for time trials)
float dummy()
{
  float f = 0.5;

  return f;
}

// generate a random integer and convert to float (dummy function)
float dummy2()
{
  int x;
  float f;

  x = random();
  f = (float) x;

  return f;
}

// generate a random float using the standard algorithm
float random_float()
{
  int x;
  float f;

  x = random();
  f = (float) x / (float)RAND_MAX;

  return f;
}


// generate a random double using the standard algorithm
float random_double()
{
  int x;
  double f;

  x = random();
  f = (double) x / (double)RAND_MAX;

  return f;
}



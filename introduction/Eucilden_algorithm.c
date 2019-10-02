#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * 欧几里德算法计算最大公因数,假定m>n
 * @param  m 较大的数
 * @param  n 较小的数
 * @return   最大公因数
 */
size_t gcd(size_t m, size_t n) {
  size_t remainder;

  while (n > 0) {
    remainder = m % n;
    m = n;
    n = remainder;
  }
  return m;
}

int main(int argc, char const *argv[]) {
  long loop_times = 10000000L;  // 循环次数
  clock_t start, finish;        // 记录开始结束时间

  printf("Time to do %ld loops is ", loop_times);
  start = clock();

  int a;
  while (loop_times--) { a = gcd(50000, 5); }

  finish = clock();
  printf("%f seconds\n", (double)(finish - start) / CLOCKS_PER_SEC);

  printf("gcd(50000,5) = %ld", a);
}
// Time to do 10000000 loops is 0.294000 seconds
// gcd(50000,3) = 1

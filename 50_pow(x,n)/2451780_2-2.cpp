/*
算法基本思想：快速幂 (Fast Exponentiation / 二分求幂)
1. 采用分治思想，将时间复杂度从 O(n) 降到 O(log n)。
2. 核心逻辑：
   - 设我们需要求 x^n。
   - 如果 n 是偶数，那么 x^n = (x^2)^(n/2)。
   - 如果 n 是奇数，那么 x^n = x * (x^2)^(n/2) (这里 n/2 是向下取整)。
3. 处理负数：如果 n < 0，我们可以将 x 变成 1/x，然后将 n 变成 -n 再进行计算。
4. 边界防溢出：在 C++ 中，32位有符号整数的范围是 [-2^31, 2^31 - 1]。如果 n = -2^31，直接执行 n = -n 会导致整型溢出。因此需要使用 long long 类型来存储 n 的值。
*/

class Solution {
public:
    double myPow(double x, int n) {
        long long N = n; 
        
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        
        double ans = 1.0;
        double current_product = x;
        
        while (N > 0) {
            if (N % 2 == 1) {
                ans *= current_product;
            }
            current_product *= current_product;
            N /= 2;
        }
        
        return ans;
    }
};
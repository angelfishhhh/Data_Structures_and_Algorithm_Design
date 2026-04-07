/*
算法基本思想：分治法 (Divide and Conquer) + 仿射变换性质
1. 核心矛盾：题目要求对于任意 i < k < j，不能出现 A[i] + A[j] = 2 * A[k]。
2. 奇偶分组：注意到等式右边 2 * A[k] 永远是偶数。如果我们让左边 A[i] 为奇数，右边 A[j] 为偶数，
   那么奇数 + 偶数 = 奇数，这个等式就永远不可能成立。
   因此，只要我们把奇数全放在数组左边，偶数全放在数组右边，跨越左右两边的任意组合必定合法。
3. 线性变换性质（仿射变换）：
   如果已知一个数组 A 是“漂亮数组”，那么对 A 中的每个元素做线性映射：
   - A * 2 (全变成偶数) 仍然是漂亮数组。
   - A * 2 - 1 (全变成奇数) 仍然是漂亮数组。
4. 迭代构造：
   - 我们可以从最简单的漂亮数组 res = [1] 起步。
   - 每次循环，利用当前的 res 构造出新的奇数漂亮数组（x * 2 - 1）和偶数漂亮数组（x * 2）。
   - 将它们拼接起来组成新的、更长的漂亮数组。
   - 在拼接时，直接过滤掉那些大于目标值 n 的元素即可。
*/

#include <vector>

class Solution {
public:
    std::vector<int> beautifulArray(int n) {
        std::vector<int> res = {1};
        
        while (res.size() < n) {
            std::vector<int> temp;
            
            for (int x : res) {
                if (x * 2 - 1 <= n) {
                    temp.push_back(x * 2 - 1);
                }
            }
            
            for (int x : res) {
                if (x * 2 <= n) {
                    temp.push_back(x * 2);
                }
            }
            
        }
        
        return res;
    }
};
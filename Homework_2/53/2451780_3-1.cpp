/*
 * 算法基本思想：动态规划 
 * 1. 状态定义：
 * 使用变量 `pre` 记录“以当前遍历到的元素结尾的连续子数组的最大和”。
 * 2. 状态转移（核心逻辑）：
 * 对于遍历到的每一个元素 `x`，我们面临两种选择：
 * - 如果前面的子数组和 `pre > 0`，说明它对当前元素有正向增益，我们将 `x` 拼接到前面的子数组中。
 * - 如果前面的子数组和 `pre <= 0`，说明它是“负资产”，只会越加越小，我们果断抛弃前面的部分，以 `x` 本身作为新子数组的起点。
 * 状态转移方程：pre = max(pre + x, x)
 */

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0;            
        int maxAns = nums[0];   
        
        for (const int& x : nums) {
            // 状态转移：接在前面，还是另起炉灶
            pre = max(pre + x, x);
            // 记录出现过的最大值
            maxAns = max(maxAns, pre);
        }
        
        return maxAns;
    }
};
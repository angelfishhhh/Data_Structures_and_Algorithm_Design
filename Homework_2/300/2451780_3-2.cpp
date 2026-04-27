/*
 * 算法基本思想：动态规划
 * 1. 状态定义：
 * dp[i] 表示以 nums[i] 这个数结尾的最长递增子序列的长度。
 * 2. 状态初始化：
 * 每个数字本身就是一个长度为 1 的子序列，所以 dp 数组全部初始化为 1。
 * 3. 状态转移：
 * 对于位置 i，我们去考察它前面的所有位置 j (0 到 i-1)。
 * 如果 nums[i] > nums[j]，说明 nums[i] 可以接在 nums[j] 后面形成一个更长的递增序列。
 * 我们就尝试更新 dp[i]：dp[i] = max(dp[i], dp[j] + 1)
 * 4. 返回结果：
 * 最长的递增子序列可能以数组中的任何一个元素结尾，因此最后返回 dp 数组中的最大值即可。
 */

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int n = nums.size();
        vector<int> dp(n, 1); 
        int maxAns = 1; 
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxAns = max(maxAns, dp[i]);
        }
        
        return maxAns;
    }
};
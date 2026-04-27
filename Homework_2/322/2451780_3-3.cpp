/*
 * 算法基本思想：动态规划
 * 1. 状态定义：
 * dp[i] 表示凑成金额 i 所需要的最少硬币个数。
 * 2. 初始化：
 * dp[0] = 0 (凑成金额 0 不需要硬币)。
 * 其余的 dp[i] 初始化为一个不可能的最大值。由于硬币面额最小为 1，凑成 amount 的硬币数最多也就是 amount 个。
 * 所以我们可以把初始值设为 amount + 1（相当于无穷大）。
 * 3. 状态转移：
 * 对于每一个金额 i (从 1 到 amount)，我们遍历所有可用的硬币面额 coin：
 * 如果当前硬币面额 <= i，说明我们可以使用这枚硬币。
 * 此时的硬币总数就是：先凑成金额 (i - coin) 的最少硬币数，再加上当前的这一枚。
 * 即：dp[i] = min(dp[i], dp[i - coin] + 1)
 * 4. 返回结果：
 * 遍历结束后，如果 dp[amount] 仍然大于 amount，说明没有任何组合能凑出该金额，返回 -1。
 * 否则返回 dp[amount]。
 */

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        
        for (int i = 1; i <= amount; ++i) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
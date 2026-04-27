/*
 * 算法基本思想：一次遍历
 * 1. 核心思路：
 * 要想获得最大利润，我们需要在最低点买入，在之后的最高点卖出。
 * 由于交易只能按时间顺序进行，我们在遍历每天股价时，只需要维护两个变量：
 * - `minPrice`: 记录到今天为止看到的最低股票价格（作为最佳买入点）。
 * - `maxProfit`: 记录到今天为止能获得的最大利润。
 * 2. 状态更新逻辑：
 * 对于每一天的价格 `price`：
 * - 如果 `price < minPrice`：说明找到了一个更便宜的买入点，更新 `minPrice`。
 * - 否则，说明今天不适合作为新的买入点，我们尝试在今天卖出：计算 `price - minPrice`，并尝试更新 `maxProfit`。
 */

 class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = 1e9;
        int maxProfit = 0;
        
        for (int price : prices) {
            if (price < minPrice) {
                minPrice = price;
            } 
            else if (price - minPrice > maxProfit) {
                maxProfit = price - minPrice;
            }
        }
        
        return maxProfit;
    }
};
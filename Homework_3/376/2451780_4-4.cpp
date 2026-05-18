/*
算法基本思想：
摆动序列要求相邻元素的差值正负交替。
因此，我们只需要统计差值符号发生变化的次数。
定义：
preDiff 表示前一段差值。
curDiff 表示当前两个元素之间的差值。
遍历数组：
1. 如果 curDiff > 0 且 preDiff <= 0，说明出现了一个上升摆动。
2. 如果 curDiff < 0 且 preDiff >= 0，说明出现了一个下降摆动。
3. 每出现一次有效摆动，答案加 1，并更新 preDiff = curDiff。
初始答案为 1，因为只要数组非空，至少可以选择一个元素作为摆动序列。
对于连续相等的元素，curDiff 为 0，不会产生摆动，直接跳过。
*/

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() <= 1) {
            return nums.size();
        }

        int ans = 1;
        int preDiff = 0;
        int curDiff = 0;

        for (int i = 1; i < nums.size(); ++i) {
            curDiff = nums[i] - nums[i - 1];

            if ((curDiff > 0 && preDiff <= 0) ||
                (curDiff < 0 && preDiff >= 0)) {
                ++ans;
                preDiff = curDiff;
            }
        }

        return ans;
    }
};
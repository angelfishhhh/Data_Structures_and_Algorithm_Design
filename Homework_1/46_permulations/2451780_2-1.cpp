/*
算法基本思想：
1. 可以把生成全排列的过程看作是遍历一棵决策树。
2. 递归函数维护一个变量 `start`，表示当前正在确定排列中第 `start` 个位置的元素。
3. 终止条件：当 `start` 等于数组的长度时，说明所有位置都已经确定，当前数组就是一个完整排列，将其加入结果的集合中。
4. 递归与回溯过程：
   - 对于当前位置 `start`，它可以是后面任意一个位置 `i`（从 `start` 到 `nums.size() - 1`）的元素。
   - 通过交换 `nums[start]` 和 `nums[i]`，把第 `i` 个元素固定在当前 `start` 位置。
   - 然后递归调用函数，去确定下一个位置。
   - 递归返回后，需要把之前交换的两个元素再换回来，以便在循环中尝试下一种情况，保证原数组的状态不被破坏。
*/

#include <vector>
#include <utility>

class Solution {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> res;
        backtrack(nums, 0, res);
        return res;
    }

private:
    void backtrack(std::vector<int>& nums, int start, std::vector<std::vector<int>>& res) {
        if (start == nums.size()) {
            res.push_back(nums);
            return;
        }
        
        for (int i = start; i < nums.size(); ++i) {
            std::swap(nums[start], nums[i]); 
            backtrack(nums, start + 1, res); 
            std::swap(nums[start], nums[i]); 
        }
    }
};
/*
算法基本思想：
每个人用 [h, k] 表示：
h 表示身高，k 表示排在该人前面且身高大于等于 h 的人数。
贪心策略：
1. 先按身高 h 从高到低排序。
2. 如果身高相同，则按 k 从小到大排序。
3. 然后依次把每个人插入结果数组的第 k 个位置。
原因：
当我们从高到低处理时，当前要插入的人之前，结果数组中已有的人身高都大于等于当前人。
因此，当前人的 k 值就等价于它应该插入的位置。
之后再插入更矮的人，不会影响已经放好的人，因为更矮的人不会被计入“身高大于等于当前人”的人数中。
*/

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) {
                return a[0] > b[0];   // 身高从高到低
            }
            return a[1] < b[1];       // 身高相同，k 从小到大
        });

        vector<vector<int>> ans;

        for (const auto& person : people) {
            ans.insert(ans.begin() + person[1], person);
        }

        return ans;
    }
};
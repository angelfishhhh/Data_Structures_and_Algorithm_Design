/*
算法基本思想：
贪心策略：
1. 先按照课程的截止时间 lastDay 从小到大排序。
   这样可以优先处理截止时间更早的课程。
2. 遍历排序后的课程，先尝试选择当前课程：
   - 将当前课程 duration 加入总耗时 totalTime；
   - 将 duration 放入最大堆。
3. 如果 totalTime > 当前课程的 lastDay，说明当前已选课程无法全部按时完成。
   此时应从已选课程中删除耗时最长的那门课。
   因为删除耗时最长的课程，可以最大程度减少总耗时，从而给后续课程留下更多时间。
4. 遍历结束后，最大堆中剩余课程数量就是最多可以修完的课程数量。
*/

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];  // 按截止时间从小到大排序
        });

        priority_queue<int> maxHeap;  // 存放已选课程的 duration，堆顶是耗时最长的课程
        int totalTime = 0;

        for (const auto& course : courses) {
            int duration = course[0];
            int lastDay = course[1];

            totalTime += duration;
            maxHeap.push(duration);

            if (totalTime > lastDay) {
                totalTime -= maxHeap.top();
                maxHeap.pop();
            }
        }

        return maxHeap.size();
    }
};
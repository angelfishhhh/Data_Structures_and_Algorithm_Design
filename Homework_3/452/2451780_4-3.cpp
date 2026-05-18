/*
算法基本思想：
每个气球可以看作一个区间 [start, end]。
一支箭射在某个 x 位置时，可以引爆所有满足 start <= x <= end 的气球。
贪心策略：
1. 按照每个气球的右边界 end 从小到大排序。
2. 优先在当前最早结束的气球的右边界射箭。
3. 这样可以在保证射爆当前气球的同时，尽可能覆盖后面更多的气球。
4. 遍历排序后的区间：
   - 如果当前气球的左边界 start <= 当前箭的位置，说明当前箭可以射爆它。
   - 如果 start > 当前箭的位置，说明当前气球无法被之前的箭射爆，需要新增一支箭，并把箭的位置更新为当前气球的右边界。
*/

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) {
            return 0;
        }

        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int arrows = 1;
        int arrowPos = points[0][1];

        for (int i = 1; i < points.size(); ++i) {
            if (points[i][0] > arrowPos) {
                ++arrows;
                arrowPos = points[i][1];
            }
        }

        return arrows;
    }
};
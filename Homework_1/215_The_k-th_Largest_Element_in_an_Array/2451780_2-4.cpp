/*
算法基本思想：最小堆 (Min-Heap)
1. 维护一个大小为 k 的最小堆。在 C++ 中，可以使用 priority_queue，并指定底层容器和比较函数使其成为小顶堆。
2. 遍历数组中的每一个元素：
   - 将当前元素压入堆中。
   - 如果此时堆的大小超过了 k，我们就把堆顶元素（即当前堆中最小的元素）弹出。
3. 通过这种“优胜劣汰”的机制，遍历完整个数组后，堆里留下来的必定是整个数组中最大的 k 个元素。
4. 因为这是一个小顶堆，所以堆顶的元素就是这 k 个最大元素中最小的那个，这正好就是我们要找的“第 k 个最大元素”。
*/

#include <vector>
#include <queue>

class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
        
        for (int num : nums) {
            minHeap.push(num);
            
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        return minHeap.top();
    }
};
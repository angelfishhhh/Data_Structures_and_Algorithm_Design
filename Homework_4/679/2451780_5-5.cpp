/*
算法基本思想：
1. 由于每一步运算都必须从当前数字集合中选出两个数字，
   对它们执行 +、-、*、/ 中的一种运算，并用结果替换这两个数字。
2. 原来有 4 个数字，每做一次运算，数字数量减少 1。
   因此经过 3 次运算后，只剩下 1 个数字。
3. 当只剩下 1 个数字时，判断它是否接近 24。
   因为除法会产生小数，所以不能直接用 == 判断，需要使用误差 EPS。
4. 对于每一层递归：
   - 枚举两个不同的数字 nums[i] 和 nums[j]；
   - 枚举它们可能产生的所有结果；
   - 把剩余数字和新结果组成下一层状态；
   - 如果某条路径能得到 24，则返回 true。
5. 加法和乘法满足交换律，可以只计算一次；
   减法和除法不满足交换律，需要分别考虑 a - b、b - a、a / b、b / a。
*/

class Solution {
public:
    bool judgePoint24(vector<int>& cards) {
        vector<double> nums;

        for (int x : cards) {
            nums.push_back(x);
        }

        return backtrack(nums);
    }

private:
    static constexpr double TARGET = 24.0;
    static constexpr double EPS = 1e-6;

    bool backtrack(vector<double>& nums) {
        int n = nums.size();

        if (n == 1) {
            return fabs(nums[0] - TARGET) < EPS;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                vector<double> nextNums;

                for (int k = 0; k < n; ++k) {
                    if (k != i && k != j) {
                        nextNums.push_back(nums[k]);
                    }
                }

                vector<double> results = calculate(nums[i], nums[j]);

                for (double value : results) {
                    nextNums.push_back(value);

                    if (backtrack(nextNums)) {
                        return true;
                    }

                    nextNums.pop_back();
                }
            }
        }

        return false;
    }

    vector<double> calculate(double a, double b) {
        vector<double> res;

        res.push_back(a + b);
        res.push_back(a - b);
        res.push_back(b - a);
        res.push_back(a * b);

        if (fabs(b) > EPS) {
            res.push_back(a / b);
        }

        if (fabs(a) > EPS) {
            res.push_back(b / a);
        }

        return res;
    }
};
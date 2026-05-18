/*
算法基本思想：
将整数 n 转成字符串，从右向左扫描。
如果发现 s[i - 1] > s[i]，说明当前位置破坏了单调递增性质。
为了让结果仍然尽可能大，应将 s[i - 1] 减 1，并记录从 i 开始的后缀需要全部改成 '9'。
继续向左扫描，可以处理类似 332、1332 这种连续回退的情况。
最后把记录位置及其右侧全部置为 '9'，得到小于等于 n 的最大单调递增数字。
*/

class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        string s = to_string(n);
        int len = s.size();
        int pos = len;  // 从 pos 开始到末尾都需要改成 '9'

        for (int i = len - 1; i > 0; --i) {
            if (s[i - 1] > s[i]) {
                s[i - 1]--;
                pos = i;
            }
        }

        for (int i = pos; i < len; ++i) {
            s[i] = '9';
        }

        return stoi(s);
    }
};
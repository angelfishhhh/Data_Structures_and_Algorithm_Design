/*
算法基本思想：
1. 定义 path 保存当前正在构造的一种切割方案，ans 保存所有合法方案。
2. 从下标 start 开始，枚举子串 s[start...i] 作为当前要切割出来的一段。
3. 如果 s[start...i] 是回文串，则把它加入 path，
   然后递归处理剩余部分 s[i + 1...n - 1]。
4. 如果 start == s.size()，说明整个字符串已经被成功切割，
   将当前 path 加入答案。
5. 递归返回后，删除刚才加入 path 的子串，继续尝试其他切割位置。
*/

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> path;

        backtrack(s, 0, path, ans);

        return ans;
    }

private:
    void backtrack(
        const string& s,
        int start,
        vector<string>& path,
        vector<vector<string>>& ans
    ) {
        if (start == s.size()) {
            ans.push_back(path);
            return;
        }

        for (int i = start; i < s.size(); ++i) {
            if (!isPalindrome(s, start, i)) {
                continue;
            }

            path.push_back(s.substr(start, i - start + 1));

            backtrack(s, i + 1, path, ans);

            path.pop_back();
        }
    }

    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }

            ++left;
            --right;
        }

        return true;
    }
};
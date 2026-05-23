/*
算法基本思想：
回溯法
1. 枚举 board 中的每一个格子，尝试把它作为 word[0] 的起点。
2. 从当前格子出发，递归匹配 word 的下一个字符。
3. 每次只能向上、下、左、右四个方向移动。
4. 为了避免同一条搜索路径中重复使用同一个格子，
   在进入递归时临时把当前格子标记为已访问，递归结束后再恢复。
5. 如果成功匹配到 word 的最后一个字符，说明单词存在，返回 true。
*/

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        if (word.size() > m * n) {
            return false;
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, word, i, j, 0)) {
                    return true;
                }
            }
        }

        return false;
    }

private:
    bool dfs(vector<vector<char>>& board, const string& word, int i, int j, int index) {
        if (index == word.size()) {
            return true;
        }

        int m = board.size();
        int n = board[0].size();

        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[index]) {
            return false;
        }

        char original = board[i][j];
        board[i][j] = '#';  // 标记当前格子已访问

        bool found =
            dfs(board, word, i + 1, j, index + 1) ||
            dfs(board, word, i - 1, j, index + 1) ||
            dfs(board, word, i, j + 1, index + 1) ||
            dfs(board, word, i, j - 1, index + 1);

        board[i][j] = original;  // 回溯，恢复现场

        return found;
    }
};
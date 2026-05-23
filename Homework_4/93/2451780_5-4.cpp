/*
算法基本思想：
1. 一个合法 IP 地址必须由 4 段组成，因此回溯过程中维护当前已经切出的段数。
2. 从当前位置 start 开始，尝试截取长度为 1、2、3 的子串作为当前 IP 段。
3. 判断当前段是否合法：
   - 长度不能超过 3；
   - 数值必须在 0 到 255 之间；
   - 如果长度大于 1，不能以 '0' 开头。
4. 如果当前段合法，则加入路径 path，继续递归处理后面的字符串。
5. 当已经切出 4 段时：
   - 如果字符串也刚好用完，则得到一个合法 IP 地址；
   - 否则该方案无效。
6. 每次递归结束后撤销选择，继续尝试其他分段方式。
*/

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> ans;
        vector<string> path;

        backtrack(s, 0, path, ans);

        return ans;
    }

private:
    void backtrack(
        const string& s,
        int start,
        vector<string>& path,
        vector<string>& ans
    ) {
        if (path.size() == 4) {
            if (start == s.size()) {
                ans.push_back(buildIp(path));
            }
            return;
        }

        // 剩余字符数量剪枝
        int remainChars = s.size() - start;
        int remainParts = 4 - path.size();

        if (remainChars < remainParts || remainChars > remainParts * 3) {
            return;
        }

        for (int len = 1; len <= 3; ++len) {
            if (start + len > s.size()) {
                break;
            }

            string segment = s.substr(start, len);

            if (!isValid(segment)) {
                continue;
            }

            path.push_back(segment);

            backtrack(s, start + len, path, ans);

            path.pop_back();
        }
    }

    bool isValid(const string& segment) {
        if (segment.size() > 1 && segment[0] == '0') {
            return false;
        }

        int value = stoi(segment);

        return value >= 0 && value <= 255;
    }

    string buildIp(const vector<string>& path) {
        string ip = path[0];

        for (int i = 1; i < 4; ++i) {
            ip += "." + path[i];
        }

        return ip;
    }
};
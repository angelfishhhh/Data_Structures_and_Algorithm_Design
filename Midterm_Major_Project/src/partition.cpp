#include <algorithm>
#include <chrono>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct Division {
    int sumA = 0;
    int sumB = 0;
    int difference = 0;
    vector<int> pileA;
    vector<int> pileB;
};

Division buildDivision(const vector<int>& values, const vector<int>& pileA) {
    vector<char> inA(values.size(), 0);
    int sumA = 0;
    for (int index : pileA) {
        inA[index - 1] = 1;
        sumA += values[index - 1];
    }

    Division result;
    result.sumA = sumA;
    result.sumB = accumulate(values.begin(), values.end(), 0) - sumA;
    result.difference = abs(result.sumA - result.sumB);
    result.pileA = pileA;
    for (int i = 0; i < static_cast<int>(values.size()); ++i) {
        if (!inA[i]) {
            result.pileB.push_back(i + 1);
        }
    }
    return result;
}

Division bruteForcePartition(const vector<int>& values) {
    int n = static_cast<int>(values.size());
    long long subsetCount = 1LL << n;
    int total = accumulate(values.begin(), values.end(), 0);
    int bestDiff = INT_MAX;
    long long bestMask = 0;

    for (long long mask = 0; mask < subsetCount; ++mask) {
        int sumA = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1LL << i)) {
                sumA += values[i];
            }
        }
        int diff = abs(total - 2 * sumA);
        if (diff < bestDiff || (diff == bestDiff && sumA < total - sumA)) {
            bestDiff = diff;
            bestMask = mask;
        }
    }

    vector<int> pileA;
    for (int i = 0; i < n; ++i) {
        if (bestMask & (1LL << i)) {
            pileA.push_back(i + 1);
        }
    }
    return buildDivision(values, pileA);
}

Division dynamicProgrammingPartition(const vector<int>& values) {
    int n = static_cast<int>(values.size());
    int total = accumulate(values.begin(), values.end(), 0);
    int target = total / 2;
    vector<vector<char>> dp(n + 1, vector<char>(target + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        int value = values[i - 1];
        for (int sum = 0; sum <= target; ++sum) {
            dp[i][sum] = dp[i - 1][sum] || (sum >= value && dp[i - 1][sum - value]);
        }
    }

    int best = target;
    while (best > 0 && !dp[n][best]) {
        --best;
    }

    vector<int> pileA;
    int sum = best;
    for (int i = n; i >= 1; --i) {
        int value = values[i - 1];
        if (sum >= value && dp[i - 1][sum - value] && !dp[i - 1][sum]) {
            pileA.push_back(i);
            sum -= value;
        }
    }
    reverse(pileA.begin(), pileA.end());
    return buildDivision(values, pileA);
}

template <typename Function>
pair<Division, long long> timedPartition(Function function) {
    auto start = chrono::high_resolution_clock::now();
    Division result = function();
    auto end = chrono::high_resolution_clock::now();
    long long elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
    return {result, elapsed};
}

void printIndices(const vector<int>& indices) {
    if (indices.empty()) {
        cout << "(empty)";
        return;
    }
    for (size_t i = 0; i < indices.size(); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << indices[i];
    }
}

void printDivision(const string& name, const Division& division, long long timeUs) {
    cout << name << " best difference: " << division.difference << '\n';
    cout << name << " pile A sum: " << division.sumA << '\n';
    cout << name << " pile A indices: ";
    printIndices(division.pileA);
    cout << '\n';
    cout << name << " pile B sum: " << division.sumB << '\n';
    cout << name << " pile B indices: ";
    printIndices(division.pileB);
    cout << '\n';
    cout << name << " time_us: " << timeUs << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> values;
    int value = 0;
    while (cin >> value) {
        if (value <= 0) {
            cerr << "All card values must be positive integers\n";
            return 1;
        }
        values.push_back(value);
    }
    if (values.empty()) {
        cerr << "Expected at least one card value\n";
        return 1;
    }

    cout << "Cards: " << values.size() << '\n';
    cout << "Total value: " << accumulate(values.begin(), values.end(), 0) << '\n';

    if (values.size() <= 22) {
        auto [brute, bruteTime] = timedPartition([&]() { return bruteForcePartition(values); });
        printDivision("BruteForce", brute, bruteTime);
    } else {
        cout << "BruteForce skipped: n exceeds 22\n";
    }

    auto [dynamic, dynamicTime] = timedPartition([&]() { return dynamicProgrammingPartition(values); });
    printDivision("DynamicProgramming", dynamic, dynamicTime);

    return 0;
}

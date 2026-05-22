#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int heapSelect(const vector<int>& values, int k) {
    vector<int> heap(values.begin(), values.begin() + k);
    make_heap(heap.begin(), heap.end());
    for (int i = k; i < static_cast<int>(values.size()); ++i) {
        if (values[i] < heap.front()) {
            pop_heap(heap.begin(), heap.end());
            heap.back() = values[i];
            push_heap(heap.begin(), heap.end());
        }
    }
    return heap.front();
}

pair<int, int> partitionThreeWay(vector<int>& values, int left, int right, int pivotValue) {
    int lt = left;
    int i = left;
    int gt = right;
    while (i <= gt) {
        if (values[i] < pivotValue) {
            swap(values[lt++], values[i++]);
        } else if (values[i] > pivotValue) {
            swap(values[i], values[gt--]);
        } else {
            ++i;
        }
    }
    return {lt, gt};
}

int randomizedSelect(vector<int> values, int k) {
    int target = k - 1;
    int left = 0;
    int right = static_cast<int>(values.size()) - 1;
    mt19937 rng(20260518);

    while (left <= right) {
        uniform_int_distribution<int> dist(left, right);
        int pivotValue = values[dist(rng)];
        pair<int, int> bounds = partitionThreeWay(values, left, right, pivotValue);
        int lt = bounds.first;
        int gt = bounds.second;
        if (target < lt) {
            right = lt - 1;
        } else if (target > gt) {
            left = gt + 1;
        } else {
            return pivotValue;
        }
    }
    throw logic_error("RandomizedSelect failed");
}

int medianOfMedians(vector<int>& values, int left, int right, int target) {
    int count = right - left + 1;
    if (count <= 5) {
        sort(values.begin() + left, values.begin() + right + 1);
        return values[target];
    }

    int medianCount = 0;
    for (int groupStart = left; groupStart <= right; groupStart += 5) {
        int groupEnd = min(groupStart + 4, right);
        sort(values.begin() + groupStart, values.begin() + groupEnd + 1);
        int medianIndex = groupStart + (groupEnd - groupStart) / 2;
        swap(values[left + medianCount], values[medianIndex]);
        ++medianCount;
    }

    int pivotValue = medianOfMedians(values, left, left + medianCount - 1, left + medianCount / 2);
    pair<int, int> bounds = partitionThreeWay(values, left, right, pivotValue);
    int lt = bounds.first;
    int gt = bounds.second;

    if (target < lt) {
        return medianOfMedians(values, left, lt - 1, target);
    }
    if (target > gt) {
        return medianOfMedians(values, gt + 1, right, target);
    }
    return pivotValue;
}

int medianOfMediansSelect(vector<int> values, int k) {
    return medianOfMedians(values, 0, static_cast<int>(values.size()) - 1, k - 1);
}

template <typename Function>
pair<int, long long> timedSelect(Function function) {
    auto start = chrono::high_resolution_clock::now();
    int result = function();
    auto end = chrono::high_resolution_clock::now();
    long long elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
    return {result, elapsed};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    int k = 0;
    if (!(cin >> n >> k)) {
        cerr << "Expected input format: n k followed by n integers\n";
        return 1;
    }
    if (n <= 0 || k < 1 || k > n) {
        cerr << "Invalid input: require n > 0 and 1 <= k <= n\n";
        return 1;
    }

    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        if (!(cin >> values[i])) {
            cerr << "Expected " << n << " integers\n";
            return 1;
        }
    }

    pair<int, long long> heapMeasured = timedSelect([&]() { return heapSelect(values, k); });
    pair<int, long long> randomMeasured = timedSelect([&]() { return randomizedSelect(values, k); });
    pair<int, long long> medianMeasured = timedSelect([&]() { return medianOfMediansSelect(values, k); });

    int heapResult = heapMeasured.first;
    long long heapTime = heapMeasured.second;
    int randomResult = randomMeasured.first;
    long long randomTime = randomMeasured.second;
    int medianResult = medianMeasured.first;
    long long medianTime = medianMeasured.second;

    cout << "Input size: " << n << '\n';
    cout << "k: " << k << '\n';
    cout << "HeapSelect: " << heapResult << " (time_us: " << heapTime << ")\n";
    cout << "RandomizedSelect: " << randomResult << " (time_us: " << randomTime << ")\n";
    cout << "MedianOfMediansSelect: " << medianResult << " (time_us: " << medianTime << ")\n";
    cout << "All algorithms agree: "
         << ((heapResult == randomResult && heapResult == medianResult) ? "yes" : "no") << '\n';

    return (heapResult == randomResult && heapResult == medianResult) ? 0 : 2;
}

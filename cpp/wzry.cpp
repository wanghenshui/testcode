#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
struct result {
    int p=0;
    int q=0;
};
bool operator <(const result& a, const result& b) {
    return (a.p < b.p || (a.p == b.p && a.q <= b.q));
}

bool operator > (const result& a, const result& b) {
    return a.p > b.p || (a.p == b.p && a.q >= b.q);
}

int main() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    if (n == m && m == 1) {
        std::cout << 1 << '\n';
        return 0;
    }
    int lines = n * (n -1) /2;
    int count = lines;
    std::map<int, result> results;
    while(lines--) {
        int x, y, a, b;
        std::cin >> x >>y >> a >> b;
        result rx = results[x];
        result ry = results[y];
        rx.q += a;
        ry.q += b;
        if (a > b) {
            rx.p += 1;
        } else {
            ry.p += 1;
        }
        results[x] = rx;
        results[y] = ry;
    }
    std::vector<result> result_filter;
    for (auto& [k, v] : results) {
        result_filter.push_back(v);
    }
    std::sort(result_filter.begin(), result_filter.end());
    /*
    for (auto v : result_filter) {
            std::cout<< "=---" << v.p << v.q << "\n";
    }
*/
    result bound_m = result_filter[result_filter.size() - m];

    for (size_t i = 1; i <= n; i++) {
        auto v = results[i];
        if (v > bound_m) {
            std::cout << 1 << '\n';  
        } else {
            std::cout << 0 << '\n';
        }
    }
}

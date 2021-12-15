#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    int dc(std::vector<int>& candies) {
        return std::min(std::unordered_set<int>(candies.begin(), candies.end()).size(), candies.size() / 2);
    }
};
#ifndef __LEETCODE__SEATCH_RANGE__
#define __LEETCODE__SEATCH_RANGE__
#include <algorithm>
#include <vector>
using std::vector;
using std::distance;
class Solution
{
public:
vector<int> searchRange (vector<int>& nums, int target) {
auto lower = lower_bound(nums.begin(), nums.end(), target);
auto uppper = upper_bound(lower, nums.end(), target);
if (lower == nums.end() || *lower != target)
return vector<int> { -1, -1 };
else
return vector<int> {distance(nums.begin(), lower), distance(nums.begin(), prev(uppper))};
}
template<typename ForwardIterator, typename T>
ForwardIterator lower_bound (ForwardIterator first,
ForwardIterator last, T value) {
while (first != last) {
auto mid = next(first, distance(first, last) / 2);
if (value > *mid) first = ++mid;
else last = mid;
}
return first;
}
template<typename ForwardIterator, typename T>
ForwardIterator upper_bound (ForwardIterator first,
ForwardIterator last, T value) {
while (first != last) {
auto mid = next(first, distance (first, last) / 2);
if (value >= *mid) first = ++mid; // 􀌽 lower_bound 􀏴􂂓􀌼􀤻
else last = mid;
}
return first;
}
};


#endif //! __LEETCODE__SEATCH_RANGE__

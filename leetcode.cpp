#include <vector>
#include <map>

class Solution {
public:
    // 1 - Two Sum
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> history;
        for (auto i = 0; i < nums.size(); ++i) {
            auto flag = history.find(target - nums[i]);
            if (flag != history.end()) return {i, flag->second};
            history[nums[i]] = i;
        }
        return {};
    }
};

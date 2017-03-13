#include "leetcode.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *    int val;
 *    ListNode *next;
 *    ListNode(int x) : val(x), next(NULL) {}
 * };
 */

vector<int> Solution::twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> history;
    for (auto i = 0; i < nums.size(); ++i) {
        auto flag = history.find(target - nums[i]);
        if (flag != history.end()) return {i, flag->second};
        history[nums[i]] = i;
    }
    return {};
}

ListNode* Solution::addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode result = ListNode(0), *current = &result;
    int prevOver = 0;
    while (l1 || l2 || prevOver) {
        int digitSum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + prevOver;
        if (digitSum < 10) {
            current->next = new ListNode(digitSum);
            prevOver = 0;
        }
        else {
            current->next = new ListNode(digitSum - 10);
            prevOver = 1;
        }
        l1 = l1 ? l1->next : nullptr;
        l2 = l2 ? l2->next : nullptr;
        current = current->next;

    }
    return result.next;
}

vector<vector<int>> Solution::threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    for (int i = 0; i < nums.size(); ++i) {
        int front = i + 1, back = nums.size() - 1, target = -nums[i];
        while (front < back) {
            int sum = nums[front] + nums[back];
            if (sum < target) front++;
            else if (sum > target) back--;
            else {
                vector<int> triplet = {nums[i], nums[front], nums[back]};
                result.push_back(triplet);
                while(front < back && nums[front] == triplet[1]) front++;
            }
        }
        while(i < nums.size() && nums[i] == nums[i + 1]) ++i;
    }
    return result;
}

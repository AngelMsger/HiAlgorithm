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
    ListNode* head = new ListNode(0), *tail = head;
    int digit_sum, prev_over = 0;
    for (; l1 && l2; l1 = l1->next, l2 = l2->next, tail = tail->next) {
        digit_sum = l1->val + l2->val + prev_over;
        if (digit_sum < 10) {
            tail->next = new ListNode(digit_sum);
            prev_over = 0;
        }
        else {
            tail->next = new ListNode(digit_sum - 10);
            prev_over = 1;
        }

    }
    ListNode *rest = l1 ? l1 : l2;
    for (; rest; rest = rest->next, tail = tail->next) {
        digit_sum = rest->val + prev_over;
        if (digit_sum < 10) {
            tail->next = new ListNode(digit_sum);
            prev_over = 0;
        }
        else {
            tail->next = new ListNode(digit_sum - 10);
            prev_over = 1;
        }
    }
    if (prev_over) {
        tail->next = new ListNode(1);
        tail = tail->next;
    }
    ListNode *result = head->next;
    delete head;
    return result;
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

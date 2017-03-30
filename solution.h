#ifndef __SOLUTION__
#define __SOLUTION__

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <iostream>
#include <iterator>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    // 1 - Two Sum
    vector<int> twoSum(vector<int>& nums, int target);

    // 2 - Add Two Numbers
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);

    // 3 - Longest Substring Without Repeating Characters
    int lengthOfLongestSubstring(string s);

    // 15 - Three Num
    vector<vector<int>> threeSum(vector<int>& nums);
};

class TestSolution {
public:
    void twoSum() noexcept;
    void addTwoNumbers() noexcept;
    void lengthOfLongestSubstring() noexcept;
    void threeSum() noexcept;
private:
    Solution mSolution;
};

#endif

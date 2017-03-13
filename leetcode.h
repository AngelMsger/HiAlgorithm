#ifndef __LEETCODE__
#define __LEETCODE__

#include <algorithm>
#include <vector>
#include <unordered_map>

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

    // 15 - Three Num
    vector<vector<int>> threeSum(vector<int>& nums);
};
#endif

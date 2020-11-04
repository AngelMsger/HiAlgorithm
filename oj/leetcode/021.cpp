/**
 * 021 - 合并两个有序链表
 * @see https://leetcode-cn.com/problems/merge-two-sorted-lists/description/
 *
 * 将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
 *
 * 示例：
 * 输入：1->2->4, 1->3->4
 * 输出：1->1->2->3->4->4
 *
 * 解题思路:
 * 简单归并。
 */

#include <iostream>
#include <chrono>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
   public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (!(l1 && l2)) return l1 ? l1 : l2;
        const auto lt = l1->val < l2->val;
        auto head = lt ? l1 : l2, candidate = lt ? l2 : l1, cur = head;
        for (; cur->next && candidate; cur = cur->next) {
            if (cur->next->val > candidate->val) swap(cur->next, candidate);
        }
        if (!cur->next) cur->next = candidate;
        return head;
    }
};

int main(int argc, char* argv[]) {
    Solution solution;

    auto print = [](ListNode* head) {
        for (auto cur = head; cur; cur = cur->next) cout << cur->val << " -> ";
        cout << endl;
    };

    auto lhs = new ListNode(0), rhs = new ListNode(1), cur = lhs;
    for (auto i = 1; i < 4; ++i) {
        cur->next = new ListNode(i * 2);
        cur = cur->next;
    }
    cur = rhs;
    for (auto i = 1; i < 4; ++i) {
        cur->next = new ListNode(i * 2 + 1);
        cur = cur->next;
    }

    print(lhs);
    print(rhs);

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.mergeTwoLists(lhs, rhs);
    auto end = chrono::high_resolution_clock::now();

    print(result);
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;

    cur = result;
    while (cur) {
        auto next = cur->next;
        delete cur;
        cur = next;
    }

    return 0;
}

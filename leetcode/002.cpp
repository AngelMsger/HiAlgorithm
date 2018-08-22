/**
 * 002 - 两数相加
 * @see https://leetcode-cn.com/problems/add-two-numbers/description/
 *
 * 给定两个非空链表来表示两个非负整数。位数按照逆序方式存储，它们的每个节点只存储单个数字。
 * 将两数相加返回一个新的链表。你可以假设除了数字 0 之外，这两个数字都不会以零开头。
 *
 * 示例：
 * 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
 * 输出：7 -> 0 -> 8
 * 原因：342 + 465 = 807
 *
 * 解题思路:
 * 比较简单的计算，注意正确理解题意。
 */

#include <bits/stdc++.h>
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
    ListNode *next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
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
};

int main(int argc, char *argv[]) {
    Solution solution;
    
    auto print = [](ListNode *head) {
        for (auto cur = head; cur; cur = cur->next) cout << cur->val << " -> ";
        cout << endl;
    };
    
    auto lhs = new ListNode(2);
    lhs->next = new ListNode(4);
    lhs->next->next = new ListNode(3);
    
    auto rhs = new ListNode(5);
    rhs->next = new ListNode(6);
    rhs->next->next = new ListNode(4);

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.addTwoNumbers(lhs, rhs);
    auto end = chrono::high_resolution_clock::now();

    print(lhs);
    print(rhs);
    print(result);
    cout << "\nin " << chrono::duration<float, milli>(end - start).count() << " ms." << endl;
    
    for (auto head: {lhs, rhs, result}) {
        auto cur = head;
        while (cur) {
            auto next = cur->next;
            delete(cur);
            cur = next;
        }
    }
    
    return 0;
}

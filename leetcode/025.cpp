/**
 * 025 - K 个一组翻转链表
 *
 * 给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。
 * k 是一个正整数，它的值小于或等于链表的长度.
 * 如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
 *
 * 示例：
 * 给你这个链表：1->2->3->4->5
 * 当 k = 2 时，应当返回: 2->1->4->3->5
 * 当 k = 3 时，应当返回: 3->2->1->4->5
 *
 * 说明：
 * 你的算法只能使用常数的额外空间。
 * 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
 */

#include <iostream>
#include <stack>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
    ListNode *mySolution(ListNode *head, int k) {
        ListNode globalHead(0);
        globalHead.next = head;
        ListNode *groupHead = &globalHead;
        ListNode *prev = groupHead,
                *cur = nullptr,
                *next = head;
        int i;
        while (groupHead->next) {
            for (i = 0; i < k && next; ++i) {
                cur = next;
                next = cur->next;
                cur->next = prev;
                // cout << "[?]set current(" << cur->val << ").next = " << (prev ? to_string(prev->val) : "NULL") << '\n';
                prev = cur;
            }
            if (i == k) {
                // finish group
                prev = groupHead->next;
                groupHead->next = cur;
                // cout << "[T]set groupHead(" << groupHead->val << ").next = " << (cur ? to_string(cur->val) : "NULL") << '\n';
                prev->next  = next;
                // cout << "[T]set prev(" << prev->val << ").next = " << (next ? to_string(next->val) : "NULL") << '\n';

                groupHead = prev;
            } else {
                groupHead = cur;
                prev = cur;
                next = cur->next;
                cur->next = nullptr;
                // rollback last group
                for (int j = 0; j < i; ++j) {
                    cur = next;
                    next = cur->next;
                    cur->next = prev;
                    // cout << "[F]set prev(" << cur->val << ").next = " << (prev ? to_string(prev->val) : "NULL") << '\n';
                    prev = cur;
                }
            }
        }
        return globalHead.next;
    }

    ListNode *betterSolution(ListNode *head, int k) {
        if (!head) return nullptr;
        ListNode *cur = head,
                 *next = nullptr,
                 *prev = nullptr;
        int i;
        for (i = 0; i < k && cur; ++i) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        if (i == k) {
            head->next = this->betterSolution(next, k);
            return prev;
        } else {
            return this->betterSolution(prev, i);
        }
    }
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        return this->betterSolution(head, k);
    }
};

int main() {
    ListNode n11(1), n12(2), n13(3), n14(4), n15(5);
    ListNode n21(1), n22(2), n23(3), n24(4), n25(5);
    n11.next = &n12;
    n12.next = &n13;
    n13.next = &n14;
    n14.next = &n15;
    n21.next = &n22;
    n22.next = &n23;
    n23.next = &n24;
    n24.next = &n25;
    Solution solution;
    auto results_1 = solution.reverseKGroup(&n11, 2);
    auto results_2 = solution.reverseKGroup(&n21, 3);

    while (results_1) {
        cout << results_1->val << ", ";
        results_1 = results_1->next;
    }
    cout << '\n';
    while (results_2) {
        cout << results_2->val << ", ";
        results_2 = results_2->next;
    }
    cout.flush();
    return 0;
}

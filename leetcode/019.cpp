/**
 * 019 - 删除链表的倒数第N个节点
 * @see
 * https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/description/
 *
 * 给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
 *
 * 示例：
 * 给定一个链表: 1->2->3->4->5, 和 n = 2.
 * 当删除了倒数第二个节点后，链表变为 1->2->3->5.
 *
 * 说明：
 * 给定的 n 保证是有效的。
 *
 * 进阶：
 * 你能尝试使用一趟扫描实现吗？
 *
 * 解题思路:
 * 两个迭代器，其中一个先走 n + 1
 * 步，然后两个一起走，先走的迭代器走到头的时候后走的迭代器的下一个位置即为
 * 倒数第 n 个。
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
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
   public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        if (!(head && n > 0)) return head;
        auto cur = head, forward = head;
        auto relative = 0;
        while (relative < n && forward) {
            forward = forward->next;
            ++relative;
        }
        if (relative == n) {
            if (forward) {
                forward = forward->next;
                while (forward) {
                    forward = forward->next;
                    cur = cur->next;
                }
                auto candidate = cur->next;
                cur->next = cur->next ? cur->next->next : nullptr;
                delete candidate;
            } else {
                head = head->next;
                delete cur;
            }
        }
        return head;
    }
};

int main(int argc, char *argv[]) {
    Solution solution;

    auto print = [](ListNode *head) {
        for (auto cur = head; cur; cur = cur->next) cout << cur->val << " -> ";
        cout << endl;
    };

    auto head = new ListNode(1), cur = head;
    for (auto i = 2; i < 6; ++i) {
        cur->next = new ListNode(i);
        cur = cur->next;
    }

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.removeNthFromEnd(head, 2);
    auto end = chrono::high_resolution_clock::now();

    print(head);
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

/**
 * 24 - 两两交换链表中的节点
 * 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
 * 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
 *
 * 示例:
 * 给定 1->2->3->4, 你应该返回 2->1->4->3.
 */

#include <iostream>
#include <vector>

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
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode front(0);
        front.next = head;
        auto *cur = head, *prev = &front;
        while (cur && cur->next) {
            prev->next = cur->next;
            swap(cur->next, cur->next->next);
            prev->next->next = cur;
            prev = cur;
            cur = cur->next;
        }
        return front.next;
    }
};

int main() {
    ListNode n1(1), n2(2), n3(3), n4(4);
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    Solution solution;
    auto *cur = solution.swapPairs(&n1);
    while (cur) {
        cout << cur->val << '\n';
        cur = cur->next;
    }
    cout.flush();
    return 0;
}

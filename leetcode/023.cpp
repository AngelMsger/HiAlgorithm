/**
 * 022 - 括号生成
 * @see https://leetcode-cn.com/problems/merge-k-sorted-lists/
 *
 * 合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。
 *
 * 示例:
 * 输入:
 * [
 *   1->4->5,
 *   1->3->4,
 *   2->6
 * ]
 * 输出: 1->1->2->3->4->4->5->6
 *
 * 解题思路:
 * 通过维护一个小顶堆来选取当前最小的若干个元素。
 */

#include <chrono>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class NPCompareContainer {
public:
    bool operator()(ListNode *lhs, ListNode* rhs) {
        return rhs->val < lhs->val;
    }
};

class Solution {
   private:
    inline ListNode* reverse_solution(vector<ListNode*>& lists) {
        vector<ListNode*> heads;
        for (auto head : lists) {
            if (head) heads.push_back(head);
        }
        auto new_head = new ListNode(0), new_cur = new_head;
        while (!heads.empty()) {
            auto min_ptr = heads.begin();
            for (auto cur = heads.begin() + 1; cur != heads.end(); ++cur)
                if (*cur && (*cur)->val < (*min_ptr)->val) min_ptr = cur;
            new_cur->next = *min_ptr;
            new_cur = new_cur->next;
            if (!(*min_ptr = (*min_ptr)->next))
                heads.erase(min_ptr, min_ptr + 1);
        }
        new_cur->next = nullptr;
        auto real = new_head->next;
        delete new_head;
        return real;
    }

    inline ListNode* heap_solution(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, NPCompareContainer> heap;
        for (auto head : lists)
            if (head) heap.push(head);
        auto fake_head = new ListNode(0), cur = fake_head;
        while (!heap.empty()) {
            auto top = heap.top();
            heap.pop();
            cur->next = top;
            cur = cur->next;
            if (top->next) heap.push(top->next);
            cur->next = nullptr;
        }
        auto real_head = fake_head->next;
        delete fake_head;
        return real_head;
    }

   public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return this->heap_solution(lists);
    }
};

int main(int argc, char* argv[]) {
    Solution solution;

    auto lhs = new ListNode(2);
    lhs->next = new ListNode(3);
    lhs->next->next = new ListNode(5);

    auto rhs = new ListNode(0);
    rhs->next = new ListNode(5);
    rhs->next->next = new ListNode(6);

    auto lists = vector<ListNode*>{lhs, rhs};

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.mergeKLists(lists);
    auto end = chrono::high_resolution_clock::now();

    for (auto cur = result; cur; cur = cur->next) cout << cur->val << ", ";
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;

    auto cur = result;
    while (cur) {
        auto next = cur->next;
        delete (cur);
        cur = next;
    }

    return 0;
}

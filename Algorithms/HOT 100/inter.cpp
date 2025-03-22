#include <iostream>
using namespace std;

// 定义链表节点结构
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 双指针法判断链表是否相交
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;  // 如果其中一个链表为空，直接返回空

    ListNode *p1 = headA, *p2 = headB;
    
    // 当p1和p2不相等时，继续循环
    while (p1 != p2) {
        // p1到达链表末尾时，指向链表B的头部
        p1 = p1 ? p1->next : headB;
        // p2到达链表末尾时，指向链表A的头部
        p2 = p2 ? p2->next : headA;
    }

    // 如果p1和p2相等，说明找到了交点，否则返回nullptr
    return p1;
}

int main() {
    // 创建链表A：1 -> 2 -> 3
    ListNode* headA = new ListNode(1);
    headA->next = new ListNode(2);
    headA->next->next = new ListNode(3);

    // 创建链表B：4 -> 5 -> 6
    ListNode* headB = new ListNode(4);
    headB->next = new ListNode(5);
    headB->next->next = new ListNode(6);

    // 创建交点链表：7 -> 8
    ListNode* intersection = new ListNode(7);
    intersection->next = new ListNode(8);

    // 连接链表A和交点链表
    headA->next->next->next = intersection;

    // 连接链表B和交点链表
    headB->next->next->next = intersection;

    // 查找交点
    ListNode* intersectionNode = getIntersectionNode(headA, headB);
    
    if (intersectionNode) {
        cout << "Intersection at node with value: " << intersectionNode->val << endl;
    } else {
        cout << "No intersection" << endl;
    }

    return 0;
}

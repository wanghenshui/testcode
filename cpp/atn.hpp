#ifndef __LEETCODE__ATN__
#define __LEETCODE__ATN__
#define ListNode
#if 0
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };
#endif

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        auto p1 = l1;
        auto p2 = l2;
        auto res = new ListNode(l1->val + l2->val);
        auto p3 = res;
        
        while(p1->next!=NULL && p2->next!=NULL)
        {
            p3->next = new ListNode(p2->next->val+p1->next->val);
            p3=p3->next;
            p2=p2->next;
            p1=p1->next;            
        }
        
        while(p1->next!=NULL)
        {
            p3->next=new ListNode(p1->next->val);
            p3=p3->next;
            p1=p1->next;
        }
        
        while(p2->next!=NULL)
        {
            p3->next=new ListNode(p2->next->val);
            p3=p3->next;
            p2=p2->next;
        }
        
        p3=res;
        while(p3->next!=NULL)
        {
            if(p3->val>=10)
            {
                p3->val%=10;
                p3->next->val++;
            }
            p3=p3->next; 
        }
        //  错在没有考虑5 5 10 这种场景
        while (p3->next == NULL && p3->val >= 10) 
        {
            p3->next = new ListNode(p3->val /10);
            p3->val %= 10;
            p3 = p3->next;
        }
        return res;
    }
};
#endif
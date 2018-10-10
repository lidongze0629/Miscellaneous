#include <iostream>
#include <memory>
#include <cassert>

typedef int DataType;
typedef unsigned Position;
enum _BOOL {
    LINKEDLIST_TRUE = 1,
    LINKEDLIST_FALSE = 0,
};

struct _ListNode {
    DataType value_;
    _ListNode* next_;
};

struct _LinkList {
    size_t size_;
    _ListNode* head_;
};

typedef _LinkList* LinkList;

_ListNode* CreateLinkNode() {
    _ListNode* listnode = reinterpret_cast<_ListNode*>(malloc(sizeof(_ListNode)));
    if (listnode == nullptr) {
        std::cout << "create link node failed." << std::endl;
        return nullptr;
    }

    listnode->value_ = 0;
    listnode->next_ = nullptr;

    return listnode;
}

LinkList CreateLinkList() {
    LinkList linklist = reinterpret_cast<LinkList>(malloc(sizeof(_LinkList)));
    if (linklist == nullptr) {
        std::cout << "create Link List failed." << std::endl;
        return nullptr;
    }

    linklist->size_ = 0;
    linklist->head_ = CreateLinkNode();

    return linklist;
}

_BOOL isEmpty(LinkList& head) {
    if (head->head_->next_ == nullptr) {
        return LINKEDLIST_TRUE;
    } else {
        return LINKEDLIST_FALSE;
    }
}

_ListNode* Locate(LinkList &head, Position position) {
    _ListNode* p = head->head_;
    Position k = 0;
    while (p != nullptr && k < position) {
        p = p->next_;
        k++;
    }
    return p;
}

_BOOL Insert(LinkList& head, Position position, DataType value) {
    if ((position == 0) || (position > head->size_ + 1)) {
        std::cout << "Invaild position." << std::endl;
        return LINKEDLIST_FALSE;
    }

    _ListNode *new_node = CreateLinkNode();
    new_node->value_ = value;

    Position pre = position - 1;
    _ListNode* pre_node = Locate(head, pre);

    new_node->next_ = pre_node->next_;
    pre_node->next_ = new_node;

    head->size_++;
    return LINKEDLIST_TRUE;   
}

_BOOL Remove(LinkList& head, Position position, DataType &value) {
    if ((position == 0) || (position > head->size_)) {
        std::cout << "Invaild position for remove" << std::endl;
        return LINKEDLIST_FALSE;
    }

    Position pre = position - 1;
    _ListNode *pre_node = Locate(head, pre);

    _ListNode *tobeRemoveNode = pre_node->next_;
    pre_node->next_ = tobeRemoveNode->next_;

    value = tobeRemoveNode->value_;
    free(tobeRemoveNode);
    head->size_--;
    return LINKEDLIST_TRUE;
}

size_t GetLength(LinkList& head) {
    assert(head != nullptr);
    return head->size_;
}

void ClearLinkList(LinkList& head) {
    _ListNode *tobeRemoveNode;
    _ListNode *first = head->head_->next_;
    while (first != nullptr) {
        tobeRemoveNode = first;
        first = first->next_;
        free(tobeRemoveNode);
    }
    
    head->size_ = 0;
    head->head_->next_ = nullptr;
}

_ListNode* Search(LinkList &head, DataType value) {
    assert(head != nullptr);

    _ListNode *first = head->head_->next_;
    while ((first != nullptr) && (first->value_ != value)) {
        first = first->next_;
    }

    return first;
}

int main() {
    LinkList linklist = CreateLinkList();
    for (unsigned i = 1; i < 100; i++) {
        Insert(linklist, i, i);
    }
    
    _ListNode *result = Search(linklist, 50);
    std::cout << result->value_ << std::endl;
}

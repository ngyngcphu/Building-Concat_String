#include "ConcatStringList.h"

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

ConcatStringList::ReferencesList::NodeRef::NodeRef(CharALNode *node, int numRef, NodeRef *next)
    : m_dataRef{node}, m_numRef{numRef}, m_nextRef{next}
{
}

void ConcatStringList::ReferencesList::prependNodeRef(CharALNode *node, int numRef)
{
    NodeRef *pNew{new NodeRef{node, numRef}};
    pNew->m_nextRef = head;
    head = pNew;
    ++countNodeRef;
}

void ConcatStringList::ReferencesList::mergeSort(NodeRef **headRef)
{
    NodeRef *head{*headRef};
    NodeRef *a{};
    NodeRef *b{};
    if ((head == nullptr) || (head->m_nextRef == nullptr))
        return;
    frontBackSplit(head, &a, &b);
    mergeSort(&a);
    mergeSort(&b);
    *headRef = sortedMerge(a, b);
}

ConcatStringList::ReferencesList::NodeRef *ConcatStringList::ReferencesList::sortedMerge(NodeRef *a, NodeRef *b)
{
    NodeRef *result{nullptr};
    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;
    if (a->m_numRef <= b->m_numRef)
    {
        result = a;
        result->m_nextRef = sortedMerge(a->m_nextRef, b);
    }
    else
    {
        result = b;
        result->m_nextRef = sortedMerge(a, b->m_nextRef);
    }
    return result;
}

void ConcatStringList::ReferencesList::frontBackSplit(NodeRef *source, NodeRef **frontRef, NodeRef **backRef)
{
    NodeRef *fast{};
    NodeRef *slow{};
    slow = source;
    fast = source->m_nextRef;
    while (fast != nullptr)
    {
        fast = fast->m_nextRef;
        if (fast != nullptr)
        {
            slow = slow->m_nextRef;
            fast = fast->m_nextRef;
        }
    }
    *frontRef = source;
    *backRef = slow->m_nextRef;
    slow->m_nextRef = nullptr;
}

ConcatStringList::DeleteStringList::NodeDel::NodeDel(ReferencesList::NodeRef *refHead, ReferencesList::NodeRef *refTail, NodeDel *next)
    : m_refHead{refHead}, m_refTail{refTail}, m_nextDel{next}
{
}

int ConcatStringList::DeleteStringList::NodeDel::totalRefCounts()
{
    if (m_refHead == m_refTail)
        return m_refHead->m_numRef;
    else
        return m_refHead->m_numRef + m_refTail->m_numRef;
}

void ConcatStringList::DeleteStringList::appendNodeDel(ReferencesList::NodeRef *nodeHead, ReferencesList::NodeRef *nodeTail)
{
    if (countNodeDel == 0)
    {
        head = tail = new NodeDel{nodeHead, nodeTail};
        ++countNodeDel;
        return;
    }
    NodeDel *pNew{new NodeDel{nodeHead, nodeTail}};
    tail->m_nextDel = pNew;
    tail = pNew;
    ++countNodeDel;
}

void ConcatStringList::DeleteStringList::removeDel(int index)
{
    if (countNodeDel == 1)
    {
        delete head;
        head = tail = nullptr;
        --countNodeDel;
    }
    else
    {
        if (index == 0)
        {
            NodeDel *temp{head};
            head = head->m_nextDel;
            delete temp;
            temp = nullptr;
            --countNodeDel;
        }
        else if (index == countNodeDel - 1)
        {
            NodeDel *pre{head};
            for (int i{0}; i < index - 1; ++i)
            {
                pre = pre->m_nextDel;
            }
            pre->m_nextDel = nullptr;
            delete tail;
            tail = pre;
            --countNodeDel;
        }
        else
        {
            NodeDel *pre{head};
            for (int i{0}; i < index - 1; ++i)
            {
                pre = pre->m_nextDel;
            }
            NodeDel *cur{pre->m_nextDel};
            pre->m_nextDel = cur->m_nextDel;
            delete cur;
            cur = nullptr;
            --countNodeDel;
        }
    }
}

ConcatStringList::CharALNode::CharArrayList::CharArrayList(const char *data)
{
    if (data != nullptr)
    {
        int length{0};
        while (data[length] != '\0')
        {
            ++length;
        }
        m_count = length;
        m_data = new char[m_count + 1];
        for (int i{0}; i <= m_count; ++i)
        {
            m_data[i] = data[i];
        }
    }
}

ConcatStringList::CharALNode::CharALNode(const char *str, CharALNode *next)
    : m_str{str}, m_next{next}
{
    m_lenNode = m_str.m_count;
}

ConcatStringList::CharALNode::~CharALNode()
{
    // if (m_str.m_data != nullptr)
    // {
    //     delete[] m_str.m_data;
    //     m_str.m_data = nullptr;
    // }
}

ConcatStringList::ConcatStringList(const char *s)
{
    if (s != nullptr)
    {
        CharALNode *p{new CharALNode{s}};
        head = tail = p;
        ++m_node;
        m_length = p->m_lenNode;

        // update ReferencesList
        refList.prependNodeRef(p, 2);
        refList.mergeSort(&refList.head);
    }
}

int ConcatStringList::length() const
{
    return m_length;
}

char ConcatStringList::get(int index) const
{
    if (index < 0 || index >= m_length)
    {
        throw std::out_of_range("Index of string is invalid!");
    }
    CharALNode *p{head};
    int temp{index};
    for (int i{0}; i < m_node; ++i)
    {
        int num{p->m_lenNode};
        if (num <= temp)
        {
            temp -= num;
            p = p->m_next;
        }
        else
            break;
    }
    return p->m_str.m_data[temp];
}

int ConcatStringList::indexOf(char c) const
{
    int temp{};
    CharALNode *p{head};
    for (int i{0}; i < m_node; ++i)
    {
        for (int j{0}; j < p->m_lenNode; ++j)
        {
            if (p->m_str.m_data[j] == c)
                return temp;
            else
                ++temp;
        }
        p = p->m_next;
    }
    return -1;
}

std::string ConcatStringList::toString() const
{
    CharALNode *p{head};
    stringstream ss;
    for (int i{0}; i < m_node; ++i)
    {
        for (int j{0}; j < p->m_lenNode; ++j)
        {
            ss << p->m_str.m_data[j];
        }
        p = p->m_next;
    }
    return ss.str();
}

ConcatStringList ConcatStringList::concat(const ConcatStringList &otherS) const
{
    ConcatStringList s{nullptr};
    tail->m_next = otherS.head;
    s.head = head;
    s.tail = otherS.tail;
    s.m_node = m_node + otherS.m_node;
    s.m_length = m_length + otherS.m_length;

    // update ReferencesList
    ReferencesList::NodeRef *p{refList.head};
    bool flagHead{false}, flagTail{false};
    for (int i{0}; i < refList.countNodeRef; ++i)
    {
        if (!flagHead)
        {
            if (p->m_dataRef == s.head)
            {
                ++p->m_numRef;
                flagHead = true;
            }
        }
        if (!flagTail)
        {
            if (p->m_dataRef == s.tail)
            {
                ++p->m_numRef;
                flagTail = true;
            }
        }
        if (flagHead && flagTail)
            break;
        p = p->m_nextRef;
    }
    refList.mergeSort(&refList.head);
    // end update ReferencesList

    return s;
}

ConcatStringList ConcatStringList::subString(int from, int to) const
{
    if (from < 0 || from >= m_length || to < 0 || to > m_length)
    {
        throw std::out_of_range("Index of string is invalid");
    }
    if (from >= to)
    {
        throw std::logic_error("Invalid range");
    }
    ConcatStringList sub{nullptr};
    CharALNode *p{};
    int tempFr{from}, tempTo{to};
    CharALNode *temp{head};
    bool flag{false};
    for (int i{0}; i < m_node; ++i)
    {
        int num = temp->m_lenNode;
        if (!flag)
        {
            if (tempFr >= num)
            {
                tempFr -= num;
                tempTo -= num;
                temp = temp->m_next;
            }
            else
            {
                if (tempTo <= num)
                {
                    char* c = new char[tempTo - tempFr + 1]{};
                    for (int j{tempFr}; j < tempTo; ++j)
                    {
                        c[j - tempFr] = temp->m_str.m_data[j];
                    }
                    sub.head = sub.tail = new CharALNode{c};
                    delete[] c;
                    sub.m_length = to - from;
                    sub.m_node = 1;

                    // update ReferencesList
                    refList.prependNodeRef(sub.head, 2);
                    refList.mergeSort(&refList.head);
                    // end update ReferencesList

                    return sub;
                }
                sub.head = new CharALNode{&temp->m_str.m_data[tempFr]};
                p = sub.head;
                ++sub.m_node;
                flag = true;
                tempTo -= num;
                temp = temp->m_next;
            }
        }
        else
        {
            if (tempTo > num)
            {
                tempTo -= num;
                p->m_next = new CharALNode{temp->m_str.m_data};
                p = p->m_next;
                ++sub.m_node;
                temp = temp->m_next;
            }
            else
            {
                CharALNode *end{new CharALNode{temp->m_str.m_data}};
                end->m_str.m_data[tempTo] = '\0';
                p->m_next = new CharALNode{end->m_str.m_data};
                p = p->m_next;
                delete end;
                ++sub.m_node;
                break;
            }
        }
    }
    sub.tail = p;
    sub.m_length = to - from;

    // update ReferencesList
    refList.prependNodeRef(sub.head, 1);
    refList.prependNodeRef(sub.tail, 1);
    refList.mergeSort(&refList.head);
    // end update ReferencesList

    return sub;
}

void ConcatStringList::prepend(const char *s)
{
    CharALNode *pNew = new CharALNode{s};
    pNew->m_next = head;
    head = pNew;
    ++m_node;
    m_length += pNew->m_lenNode;
}

ConcatStringList ConcatStringList::reverse() const
{
    ConcatStringList res{nullptr};
    CharALNode *temp{head};
    for (int i{0}; i < m_node; ++i)
    {
        int num = temp->m_lenNode;
        char* c = new char[num + 1]{};
        for (int j{0}; j < num; ++j)
        {
            c[j] = temp->m_str.m_data[num - 1 - j];
        }
        if (i == 0)
        {
            res.head = res.tail = new CharALNode{c};
        }
        else
        {
            res.prepend(c);
        }
        temp = temp->m_next;
        delete[] c;
    }
    res.m_length = m_length;
    res.m_node = m_node;

    // update ReferencesList
    if (m_node == 1)
    {
        refList.prependNodeRef(res.head, 2);
        refList.mergeSort(&refList.head);
    }
    else if (m_node > 1)
    {
        refList.prependNodeRef(res.head, 1);
        refList.prependNodeRef(res.tail, 1);
        refList.mergeSort(&refList.head);
    }
    // end update ReferencesList

    return res;
}

ConcatStringList::~ConcatStringList()
{
    ReferencesList::NodeRef *p1{refList.head};
    ReferencesList::NodeRef *p2{refList.head};
    bool flagHead{false}, flagTail{false};
    int num{refList.countNodeRef};
    for (int i{0}; i < num; ++i)
    {
        if (!flagHead)
        {
            if (p1->m_dataRef == this->head)
            {
                --p1->m_numRef;
                flagHead = true;
            }
        }
        if (!flagTail)
        {
            if (p2->m_dataRef == this->tail)
            {
                --p2->m_numRef;
                flagTail = true;
            }
        }
        if (flagHead && flagTail)
            break;
        if (!flagHead)
            p1 = p1->m_nextRef;
        if (!flagTail)
            p2 = p2->m_nextRef;
    }
    delStrList.appendNodeDel(p1, p2);
    DeleteStringList::NodeDel *del{delStrList.head};
    for (int i{0}; i < delStrList.countNodeDel; ++i)
    {
        if (del->totalRefCounts() == 0)
        {
            // deallocate CharALNode
            CharALNode *nodeHead{del->m_refHead->m_dataRef};
            CharALNode *nodeTail{del->m_refTail->m_dataRef};            
            CharALNode *temp{nodeHead};
            // while (nodeHead != nullptr)
            // {
            //     nodeHead = nodeHead->m_next;
            //     if (temp != nullptr)
            //     {
            //         delete temp;
            //         temp = nullptr;
            //     }
            //     temp = nodeHead;
            // }
            nodeTail = nullptr;
            // end deallocate CharALNode

            del = del->m_nextDel;
            delStrList.removeDel(i);
            --i;
            continue;
        }
        del = del->m_nextDel;
    }
    refList.mergeSort(&refList.head);
    ReferencesList::NodeRef *tailRef{refList.head};
    for (int i{0}; i < refList.countNodeRef - 1; ++i)
    {
        tailRef = tailRef->m_nextRef;
    }
    ReferencesList::NodeRef *checkZero{};
    int cnt{0};
    while (refList.head->m_numRef == 0)
    {
        ++cnt;
        if (cnt == refList.countNodeRef)
        {
            break;
        }
        checkZero = refList.head;
        refList.head = refList.head->m_nextRef;
        checkZero->m_nextRef = nullptr;
        tailRef->m_nextRef = checkZero;
        tailRef = checkZero;
    }
    
    ReferencesList::NodeRef *pRef{refList.head};
    if (refList.head->m_numRef == 0)
    {
        while (refList.head != nullptr)
        {
            refList.head = refList.head->m_nextRef;
            if (pRef != nullptr)
            {
                delete pRef;
                pRef = nullptr;
            }
            pRef = refList.head;
        }
        refList.countNodeRef = 0;
    }
}

int ConcatStringList::ReferencesList::size() const
{
    return countNodeRef;
}

int ConcatStringList::ReferencesList::refCountAt(int index) const
{
    if (index < 0 || index >= countNodeRef)
    {
        throw std::out_of_range("Index of references list is invalid!");
    }
    NodeRef *p{head};
    for (int i{0}; i < index; ++i)
    {
        p = p->m_nextRef;
    }
    return p->m_numRef;
}

std::string ConcatStringList::ReferencesList::refCountsString() const
{
    NodeRef *p{head};
    stringstream ss;
    ss << "RefCounts[";
    for (int i{0}; i < countNodeRef - 1; ++i)
    {
        ss << p->m_numRef << ",";
        p = p->m_nextRef;
    }
    if (countNodeRef > 0)
    {
        ss << p->m_numRef << "]";
    }
    else
    {
        ss << "]";
    }
    return ss.str();
}

int ConcatStringList::DeleteStringList::size() const
{
    return countNodeDel;
}

std::string ConcatStringList::DeleteStringList::totalRefCountsString() const
{
    NodeDel *p{head};
    stringstream ss;
    ss << "TotalRefCounts[";
    for (int i{0}; i < countNodeDel - 1; ++i)
    {
        ss << p->totalRefCounts() << ",";
        p = p->m_nextDel;
    }
    if (countNodeDel > 0)
    {
        ss << p->totalRefCounts() << "]";
    }
    else
    {
        ss << "]";
    }
    return ss.str();
}
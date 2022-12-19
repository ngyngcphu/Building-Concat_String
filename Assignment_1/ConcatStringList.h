#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class ConcatStringList
{
public:
    class ReferencesList;   // forward declaration
    class DeleteStringList; // forward declaration
    class CharALNode;

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    // TODO: may provide some attributes
    CharALNode *head{};
    CharALNode *tail{};
    int m_node{};
    int m_length{};

private:
    void prepend(const char *s);

public:
    ConcatStringList(const char *);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList &otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    ~ConcatStringList();

public:
    class ReferencesList
    {
        // TODO: may provide some attributes
    public:
        class NodeRef
        {
        public:
            CharALNode *m_dataRef{};
            int m_numRef{};
            NodeRef *m_nextRef{};

        public:
            NodeRef(CharALNode *node = nullptr, int numRef = 0, NodeRef *next = nullptr);
        };

    public:
        NodeRef *head{};
        int countNodeRef{};

    public:
        void prependNodeRef(CharALNode *node, int numRef);
        void mergeSort(NodeRef **headRef);
        NodeRef *sortedMerge(NodeRef *a, NodeRef *b);
        void frontBackSplit(NodeRef *source, NodeRef **frontRef, NodeRef **backRef);

    public:
        int size() const;
        int refCountAt(int index) const;
        std::string refCountsString() const;
    };

    class DeleteStringList
    {
        // TODO: may provide some attributes
    public:
        class NodeDel
        {
        public:
            ReferencesList::NodeRef *m_refHead{};
            ReferencesList::NodeRef *m_refTail{};
            NodeDel *m_nextDel{};

        public:
            NodeDel(ReferencesList::NodeRef *refHead = nullptr, ReferencesList::NodeRef *refTail = nullptr, NodeDel *next = nullptr);
            int totalRefCounts();
        };

    public:
        NodeDel *head{};
        NodeDel *tail{};
        int countNodeDel{};

    public:
        void appendNodeDel(ReferencesList::NodeRef *nodeHead, ReferencesList::NodeRef *nodeTail);
        void removeDel(int index);

    public:
        int size() const;
        std::string totalRefCountsString() const;
    };

    class CharALNode
    {
    public:
        class CharArrayList
        {
        public:
            char *m_data{};
            int m_count{};

        public:
            CharArrayList(const char *data = nullptr);
        };

    public:
        CharArrayList m_str{};
        CharALNode *m_next{};
        int m_lenNode{};

    public:
        CharALNode(const char *str = nullptr, CharALNode *next = nullptr);
        ~CharALNode();
    };
};

#endif // __CONCAT_STRING_LIST_H__
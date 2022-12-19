#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

class ParentsTree;

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

class BSTNode
{
private:
    string data{};
    BSTNode *left{};
    BSTNode *right{};
    int key{};
    int size{};
    ParentsTree *papa{};
    int id{};
    friend class ConcatStringTree;

public:
    BSTNode(const string &s, int size, int id);
    ~BSTNode();
};

class ConcatStringTree
{
private:
    BSTNode *root{};

protected:
    char getRec(BSTNode *root, int index) const;
    int indexOfRec(BSTNode *root, char c, int &sum) const;
    string toStringPreOrderRec(BSTNode *root) const;
    string toStringRec(BSTNode *root) const;
    ConcatStringTree *subStringRec(BSTNode *root, int &from, int &to) const;
    string reverseString(const string &str) const;
    ConcatStringTree *reverseRec(BSTNode *root) const;

public:
    ConcatStringTree(const char *s);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    string toStringPreOrder() const;
    string toString() const;
    ConcatStringTree concat(const ConcatStringTree &otherS) const;
    ConcatStringTree subString(int from, int to) const;
    ConcatStringTree reverse() const;
    //~ConcatStringTree();

    int getParTreeSize(const string &query) const;
    string getParTreeStringPreOrder(const string &query) const;
};

class AVLNode
{
private:
    int id{};
    AVLNode *left{};
    AVLNode *right{};
    BalanceValue balance{};
    friend class ParentsTree;

public:
    AVLNode(int id) : id{id}, left{nullptr}, right{nullptr}, balance{EH}
    {
    }
    //~AVLNode();
};

class ParentsTree
{
private:
    AVLNode *root{};
    int numAVLNode{};

public:
    static int idMax;
    static long long power(int base, int exp);

protected:
    void rotateLeft(AVLNode *&root);
    void rotateRight(AVLNode *&root);
    bool balanceLeft(AVLNode *&root);
    bool balanceRight(AVLNode *&root);
    bool insertRec(AVLNode *&root, int value);

    bool deleteBalanceLeft(AVLNode *&root);
    bool deleteBalanceRight(AVLNode *&root);
    bool removeRec(AVLNode *&, int value);

    string toStringPreOrderRec(AVLNode *root) const;

public:
    ParentsTree() : root{nullptr}, numAVLNode{0}
    {
    }
    void insert(int value);
    void remove(int value);
    int size() const;
    string toStringPreOrder() const;
    ~ParentsTree();
};

class ReducedConcatStringTree; // forward declaration
class LitStringHash;           // forward declaration

class HashConfig
{
private:
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;

    friend class ReducedConcatStringTree;
    friend class LitStringHash;

public:
    HashConfig(int p = 0, double c1 = 0.0, double c2 = 0.0, double lambda = 0.0, double alpha = 0.0, int initSize = 0)
        : p{p}, c1{c1}, c2{c2}, lambda{lambda}, alpha{alpha}, initSize{initSize}
    {
    }
    //~HashConfig();
};

class LitString
{
public:
    string s{};
    int numP{};
    friend class ListStringHash;

public:
    LitString(const string &s = "", int numP = 0) : s{s}, numP{numP}
    {
    }
    //~LitString();
};

enum STATUS_TYPE
{
    NIL,
    NON_EMPTY,
    DELETED
};

class LitStringHash
{
private:
    HashConfig hash{};
    int lastInsertedIndex{};
    LitString *litString{};
    int size{};
    STATUS_TYPE *status;

public:
    LitStringHash(const HashConfig &hashConfig);
    int getLastInsertedIndex() const;
    string toString() const;
    static int hashFunction(const string &s, int m, int p);
    static int quadraticProbing(const string &s, int i, int m, int p, int c1, int c2);
    int insertLitStringHash(const string& s);
    ~LitStringHash();
};

class ReducedConcatStringTree : public ConcatStringTree /* */
{
public:
    ReducedConcatStringTree(const char *s, LitStringHash *litStringHash);
    LitStringHash *litStringHash{};
    ~ReducedConcatStringTree();
};

#endif // __CONCAT_STRING_TREE_H__
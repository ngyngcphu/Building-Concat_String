#include "ConcatStringTree.h"

int ParentsTree::idMax{0};
long long ParentsTree::power(int base, int exp)
{
    int result{1};
    for (int i{0}; i < exp; ++i)
    {
        result *= base;
    }
    return result;
}

BSTNode::BSTNode(const string &s, int size, int id)
    : data{s}, left{nullptr}, right{nullptr}, key{0}, size{size}
{
    if (id > ParentsTree::power(10, 7))
    {
        throw overflow_error("Id is overflow!");
    }
    this->id = id;
    this->papa = new ParentsTree{};
}

ConcatStringTree::ConcatStringTree(const char *s)
{
    string newLeaf{};
    int sLength{};
    while (s[sLength] != '\0')
    {
        newLeaf += s[sLength];
        ++sLength;
    }
    root = new BSTNode{newLeaf, sLength, ++ParentsTree::idMax};
    // update ParentsTree
    root->papa->insert(root->id);
    // done
}

int ConcatStringTree::length() const
{
    return root->size;
}

char ConcatStringTree::getRec(BSTNode *root, int index) const
{
    if (!root)
    {
        return '\0';
    }
    if (index >= length())
    {
        throw out_of_range("Index of string is invalid!");
    }
    if (!root->left && !root->right)
    {
        return root->data[index];
    }
    else
    {
        if (index < root->key)
        {
            return getRec(root->left, index);
        }
        else
        {
            return getRec(root->right, index - root->key);
        }
    }
}

char ConcatStringTree::get(int index) const
{
    return getRec(root, index);
}

int ConcatStringTree::indexOfRec(BSTNode *root, char c, int &sum) const
{
    if (!root)
    {
        return -1;
    }
    if (!root->left && !root->right)
    {
        for (int i{0}; i < root->size; ++i)
        {
            if (root->data[i] == c)
            {
                return i;
            }
            sum += 1;
        }
        return -1;
    }
    if (indexOfRec(root->left, c, sum) != -1 || indexOfRec(root->right, c, sum) != -1)
    {
        return sum;
    }
    return -1;
}

int ConcatStringTree::indexOf(char c) const
{
    int sum{};
    return indexOfRec(root, c, sum);
}

string ConcatStringTree::toStringPreOrderRec(BSTNode *root) const
{
    stringstream ss;
    if (!root)
    {
        return ss.str();
    }
    ss << "(LL=" << root->key << ",L=" << root->size << ",";
    (root->data == "" ? ss << "<NULL>" : ss << "\"" << root->data << "\"") << ");";
    ss << toStringPreOrderRec(root->left);
    ss << toStringPreOrderRec(root->right);
    return ss.str();
}

string ConcatStringTree::toStringPreOrder() const
{
    stringstream ss;
    ss << "ConcatStringTree[" << toStringPreOrderRec(root);
    string s{ss.str()};
    s[s.size() - 1] = ']';
    return s;
}

string ConcatStringTree::toStringRec(BSTNode *root) const
{
    stringstream ss;
    if (!root)
    {
        return ss.str();
    }
    if (!root->left && !root->right)
    {
        ss << root->data;
        return ss.str();
    }
    return toStringRec(root->left) + toStringRec(root->right);
}

string ConcatStringTree::toString() const
{
    stringstream ss;
    ss << "ConcatStringTree[\"" << toStringRec(root) << "\"]";
    return ss.str();
}

ConcatStringTree ConcatStringTree::concat(const ConcatStringTree &otherS) const
{
    ConcatStringTree newTree{""};
    newTree.root->left = root;
    newTree.root->right = otherS.root;
    newTree.root->key = length();
    newTree.root->size = length() + otherS.length();
    // update ParentsTree of *this and otherS
    root->papa->insert(newTree.root->id);
    otherS.root->papa->insert(newTree.root->id);
    // done
    return newTree;
}

ConcatStringTree *ConcatStringTree::subStringRec(BSTNode *root, int &from, int &to) const
{
    if (!root || from >= to)
    {
        return nullptr;
    }
    ConcatStringTree *subLeft{subStringRec(root->left, from, to)};
    ConcatStringTree *subRight{subStringRec(root->right, from, to)};
    if (root->left || root->right)
    {
        if (!subLeft && !subRight)
        {
            return nullptr;
        }
        if (!subLeft)
        {
            ConcatStringTree *temp{new ConcatStringTree{""}};
            temp->root->right = subRight->root;
            temp->root->size = subRight->length();
            // update ParentsTree of temp
            temp->root->papa->insert(temp->root->id);
            // done
            return temp;
        }
        else if (!subRight)
        {
            ConcatStringTree *temp{new ConcatStringTree{""}};
            temp->root->left = subLeft->root;
            temp->root->size = subLeft->length();
            temp->root->key = subLeft->length();
            // update ParentsTree of temp
            temp->root->papa->insert(temp->root->id);
            // done
            return temp;
        }
        else
        {
            return new ConcatStringTree{subLeft->concat(*subRight)};
        }
    }
    string subTree{};
    if (root->size <= to)
    {
        if (root->size <= from)
        {
            from -= root->size;
            to -= root->size;
            return nullptr;
        }
        else
        {
            subTree = root->data.substr(from, root->size);
            from = 0;
            to -= root->size;
        }
    }
    else
    {
        subTree = root->data.substr(from, to - from);
        to -= root->size;
    }
    ConcatStringTree *temp{new ConcatStringTree{""}};
    temp->root->data = subTree;
    temp->root->size = subTree.size();
    // update ParentsTree of temp
    temp->root->papa->insert(temp->root->id);
    // done
    return temp;
}

ConcatStringTree ConcatStringTree::subString(int from, int to) const
{
    if (from < 0 || from >= length() || to < 0 || to > length())
    {
        throw out_of_range("Index of string is invalid!");
    }
    if (from >= to)
    {
        throw logic_error("Invalid range!");
    }
    return *subStringRec(root, from, to);
}

string ConcatStringTree::reverseString(const string &str) const
{
    string res{};
    for (int i = str.size() - 1; i >= 0; --i)
    {
        res += str[i];
    }
    return res;
}

ConcatStringTree *ConcatStringTree::reverseRec(BSTNode *root) const
{
    if (!root)
    {
        return nullptr;
    }
    ConcatStringTree *revLeft{reverseRec(root->left)};
    ConcatStringTree *revRight{reverseRec(root->right)};
    if (root->left || root->right)
    {
        if (!revLeft && !revRight)
        {
            return nullptr;
        }
        if (!revLeft)
        {
            ConcatStringTree *temp{new ConcatStringTree{""}};
            temp->root->left = revRight->root;
            temp->root->size = revRight->length();
            temp->root->key = revRight->length();
            // update ParentsTree of temp
            temp->root->papa->insert(temp->root->id);
            // done
            return temp;
        }
        else if (!revRight)
        {
            ConcatStringTree *temp{new ConcatStringTree{""}};
            temp->root->right = revLeft->root;
            temp->root->size = revLeft->length();
            // update ParentsTree of temp
            temp->root->papa->insert(temp->root->id);
            // done
            return temp;
        }
        else
        {
            return new ConcatStringTree{revRight->concat(*revLeft)};
        }
    }
    ConcatStringTree *temp{new ConcatStringTree{""}};
    temp->root->data = reverseString(root->data);
    temp->root->size = root->data.size();
    // update ParentsTree of temp
    temp->root->papa->insert(temp->root->id);
    // done
    return temp;
}

ConcatStringTree ConcatStringTree::reverse() const
{
    return *reverseRec(root);
}

void ParentsTree::rotateLeft(AVLNode *&root)
{
    AVLNode *temp{root->right};
    root->right = temp->left;
    temp->left = root;
    root = temp;
}

void ParentsTree::rotateRight(AVLNode *&root)
{
    AVLNode *temp{root->left};
    root->left = temp->right;
    temp->right = root;
    root = temp;
}

bool ParentsTree::balanceLeft(AVLNode *&root)
{
    if (root->balance == EH)
    {
        root->balance = LH;
        return true;
    }
    else if (root->balance == RH)
    {
        root->balance = EH;
        return false;
    }
    else
    {
        if (root->left->balance == LH)
        {
            rotateRight(root);
            root->balance = EH;
            root->right->balance = EH;
        }
        else if (root->left->balance == RH)
        {
            rotateLeft(root->left);
            rotateRight(root);
            if (root->balance == EH)
            {
                root->left->balance = EH;
                root->right->balance = EH;
            }
            else if (root->balance == LH)
            {
                root->balance = EH;
                root->left->balance = EH;
                root->right->balance = RH;
            }
            else
            {
                root->balance = EH;
                root->left->balance = LH;
                root->right->balance = EH;
            }
        }
        return false;
    }
}

bool ParentsTree::balanceRight(AVLNode *&root)
{
    if (root->balance == EH)
    {
        root->balance = RH;
        return true;
    }
    else if (root->balance == LH)
    {
        root->balance = EH;
        return false;
    }
    else
    {
        if (root->right->balance == RH)
        {
            rotateLeft(root);
            root->balance = EH;
            root->left->balance = EH;
        }
        else if (root->right->balance == LH)
        {
            rotateRight(root->right);
            rotateLeft(root);
            if (root->balance == EH)
            {
                root->left->balance = EH;
                root->right->balance = EH;
            }
            else if (root->balance == LH)
            {
                root->balance = EH;
                root->left->balance = EH;
                root->right->balance = RH;
            }
            else
            {
                root->balance = EH;
                root->left->balance = LH;
                root->right->balance = EH;
            }
        }
        return false;
    }
}

bool ParentsTree::insertRec(AVLNode *&root, int value)
{
    if (!root)
    {
        root = new AVLNode{value};
        ++numAVLNode;
        return true;
    }
    if (value < root->id)
    {
        bool higher{insertRec(root->left, value)};
        if (higher)
        {
            return balanceLeft(root);
        }
        else
        {
            return false;
        }
    }
    else
    {
        bool higher{insertRec(root->right, value)};
        if (higher)
        {
            return balanceRight(root);
        }
        else
        {
            return false;
        }
    }
}

void ParentsTree::insert(int value)
{
    insertRec(root, value);
}

bool ParentsTree::deleteBalanceLeft(AVLNode *&root)
{
    if (root->balance == EH)
    {
        root->balance = LH;
        return false;
    }
    else if (root->balance == RH)
    {
        root->balance = EH;
        return true;
    }
    else
    {
        if (root->left->balance == LH)
        {
            rotateRight(root);
            root->balance = EH;
            root->right->balance = EH;
            return true;
        }
        else if (root->left->balance == RH)
        {
            rotateLeft(root->left);
            rotateRight(root);
            if (root->balance == EH)
            {
                root->left->balance = EH;
                root->right->balance = EH;
            }
            else if (root->balance == LH)
            {
                root->balance = EH;
                root->left->balance = EH;
                root->right->balance = RH;
            }
            else
            {
                root->balance = EH;
                root->left->balance = LH;
                root->right->balance = EH;
            }
            return true;
        }
        else
        {
            rotateRight(root);
            root->balance = RH;
            root->right->balance = LH;
        }
        return false;
    }
}

bool ParentsTree::deleteBalanceRight(AVLNode *&root)
{
    if (root->balance == EH)
    {
        root->balance = RH;
        return false;
    }
    else if (root->balance == LH)
    {
        root->balance = EH;
        return true;
    }
    else
    {
        if (root->right->balance == RH)
        {
            rotateLeft(root);
            root->balance = EH;
            root->left->balance = EH;
            return true;
        }
        else if (root->right->balance == LH)
        {
            rotateRight(root->right);
            rotateLeft(root);
            if (root->balance == EH)
            {
                root->left->balance = EH;
                root->right->balance = EH;
            }
            else if (root->balance == LH)
            {
                root->balance = EH;
                root->left->balance = EH;
                root->right->balance = RH;
            }
            else
            {
                root->balance = EH;
                root->left->balance = LH;
                root->right->balance = EH;
            }
            return true;
        }
        else
        {
            rotateLeft(root);
            root->balance = LH;
            root->left->balance = RH;
        }
        return false;
    }
}

bool ParentsTree::removeRec(AVLNode *&, int value)
{
    if (!root)
    {
        return false;
    }
    if (value < root->id)
    {
        bool shorter{removeRec(root->left, value)};
        if (shorter)
        {
            return balanceRight(root);
        }
        else
        {
            return false;
        }
    }
    else if (value > root->id)
    {
        bool shorter{removeRec(root->right, value)};
        if (shorter)
        {
            return balanceLeft(root);
        }
        else
        {
            return false;
        }
    }
    else
    {
        AVLNode *dltNode{root};
        if (!root->left)
        {
            root = root->right;
            delete dltNode;
            --numAVLNode;
            return true;
        }
        else if (!root->right)
        {
            root = root->left;
            delete dltNode;
            --numAVLNode;
            return true;
        }
        else
        {
            AVLNode *p{root->left};
            while (p->right)
            {
                p = p->right;
            }
            root->id = p->id;
            bool shorter{removeRec(root->left, p->id)};
            if (shorter)
            {
                return balanceRight(root);
            }
            else
            {
                return false;
            }
        }
    }
}

void ParentsTree::remove(int value)
{
    removeRec(root, value);
}

int ParentsTree::size() const
{
    return numAVLNode;
}

string ParentsTree::toStringPreOrderRec(AVLNode *root) const
{
    stringstream ss;
    if (!root)
    {
        return ss.str();
    }
    ss << "(id=" << root->id << ");";
    ss << toStringPreOrderRec(root->left);
    ss << toStringPreOrderRec(root->right);
    return ss.str();
}

string ParentsTree::toStringPreOrder() const
{
    stringstream ss;
    ss << "ParentsTree[";
    if (numAVLNode)
    {
        ss << toStringPreOrderRec(root);
        string s{ss.str()};
        s[s.size() - 1] = ']';
        return s;
    }
    else
    {
        ss << "]";
    }
    return ss.str();
}

int ConcatStringTree::getParTreeSize(const string &query) const
{
    if (query == "")
    {
        return root->papa->size();
    }
    BSTNode *walker{root};
    int l = query.size();
    for (int i{0}; i < l - 1; ++i)
    {
        if (query[i] != 'l' && query[i] != 'r')
        {
            throw runtime_error("Invalid character of query");
        }
        if (!walker)
        {
            throw runtime_error("Invalid query: reaching NULL");
        }
        if (query[i] == 'l')
        {
            walker = walker->left;
        }
        else
        {
            walker = walker->right;
        }
    }
    if (query[l - 1] == 'l')
    {
        return walker->papa->size();
    }
    else if (query[l - 1] == 'r')
    {
        return walker->papa->size();
    }
    else
    {
        throw runtime_error("Invalid query: reaching NULL");
    }
}

string ConcatStringTree::getParTreeStringPreOrder(const string &query) const
{
    if (query == "")
    {
        return root->papa->toStringPreOrder();
    }
    BSTNode *walker{root};
    int l = query.size();
    for (int i{0}; i < l - 1; ++i)
    {
        if (query[i] != 'l' && query[i] != 'r')
        {
            throw runtime_error("Invalid character of query");
        }
        if (!walker)
        {
            throw runtime_error("Invalid query: reaching NULL");
        }
        if (query[i] == 'l')
        {
            walker = walker->left;
        }
        else
        {
            walker = walker->right;
        }
    }
    if (query[l - 1] == 'l')
    {
        return walker->papa->toStringPreOrder();
    }
    else if (query[l - 1] == 'r')
    {
        return walker->papa->toStringPreOrder();
    }
    else
    {
        throw runtime_error("Invalid query: reaching NULL");
    }
}

LitStringHash::LitStringHash(const HashConfig &hashConfig)
{
    hash = hashConfig;
    lastInsertedIndex = -1;
    litString = new LitString[hashConfig.initSize];
    size = 0;
    this->status = new STATUS_TYPE[hashConfig.initSize]{NIL};
}

int LitStringHash::hashFunction(const string &s, int m, int p)
{
    long long sum{};
    for (int i{0}; i < (int)s.size(); ++i)
    {
        sum += (((int)s[i] * ParentsTree::power(p, i)) % m);
    }
    return sum % m;
}

int LitStringHash::quadraticProbing(const string &s, int i, int m, int p, int c1, int c2)
{
    return ((hashFunction(s, m, p) + c1 * i + c2 * i * i) % m);
}

int LitStringHash::insertLitStringHash(const string &s)
{
    bool found{false};
    for (int i{0}; i < hash.initSize; ++i)
    {
        int slot{quadraticProbing(s, i, hash.initSize, hash.p, hash.c1, hash.c2)};
        if (litString[slot].s == s)
        {
            ++litString[slot].numP;
            found = true;
            break;
        }
        else if (status[slot] == NIL || status[slot] == DELETED)
        {
            litString[slot].s = s;
            ++litString[slot].numP;
            status[slot] = NON_EMPTY;
            ++size;
            found = true;
            break;
        }
    }
    if (!found)
    {
        throw runtime_error("No possible slot");
    }
    double load = size / (double)hash.initSize;
    if (load > hash.lambda)
    {
        int newSize{(int)(hash.alpha * size)};
        hash.initSize = newSize;
        LitString *tempLit{new LitString[newSize]{}};
        STATUS_TYPE *tempSta{new STATUS_TYPE[newSize]{NIL}};
        for (int i{0}; i < size; ++i)
        {
            if (status[i] == NON_EMPTY)
            {
                for (int i{0}; i < hash.initSize; ++i)
                {
                    int slot{quadraticProbing(s, i, hash.initSize, hash.p, hash.c1, hash.c2)};
                    if (tempSta[slot] == NIL || tempSta[slot] == DELETED)
                    {
                        tempLit[slot].s = s;
                        ++tempLit[slot].numP;
                        tempSta[slot] = NON_EMPTY;
                        lastInsertedIndex = slot;
                    }
                }
            }
        }
        delete[] litString;
        delete[] status;
        litString = tempLit;
        status = tempSta;
    }
    return lastInsertedIndex;
}

int LitStringHash::getLastInsertedIndex() const
{
    return lastInsertedIndex;
}

string LitStringHash::toString() const
{
    string res{"LitStringHash["};
    if (size != 0)
    {
        for (int i{0}; i < hash.initSize; ++i)
        {
            res += (litString[i].numP > 0) ? "litS=\"" + litString[i].s + "\");" : "();";
        }
        res[res.length() - 1] = ']';
    }
    else
    {
        res += "]";
    }
    return res;
}

ReducedConcatStringTree::ReducedConcatStringTree(const char *s, LitStringHash *litStringHash) : ConcatStringTree(s)
{
    this->litStringHash = litStringHash;
    this->litStringHash->insertLitStringHash(s);
}
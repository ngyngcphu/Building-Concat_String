#include "ConcatStringTree.h"

void test1()
{
    cout << "Test1: \n";
    ConcatStringTree s1("Hello");
    ConcatStringTree s2(",_t");
    ConcatStringTree s3("his_is");
    ConcatStringTree s4("_an");

    ConcatStringTree subtree1 = s1.concat(s2);
    ConcatStringTree subtree2 = s3.concat(s4);
    ConcatStringTree tree = subtree1.concat(subtree2);

    cout << "-> Structure of the tree: " << tree.toStringPreOrder() << endl;
    cout << "sTRING: " << tree.toString() << endl;
    cout << "[h] - " << tree.get(8) << endl;
    cout << "[6] - " << tree.indexOf('_') << endl;

    cout << "-> Now we take substring (7 -> 14)" << endl;
    ConcatStringTree subStringTree = tree.subString(7, 14);
    cout << "Structure of the tree: " << subStringTree.toStringPreOrder() << endl;
    cout << "sTRING: " << subStringTree.toString() << endl;
    cout << "[s] - " << subStringTree.get(6) << endl;
    cout << "[4] - " << subStringTree.indexOf('_') << endl;

    cout << "-> Go back to the original tree, we take substring (2 -> 8)" << endl;
    ConcatStringTree subStringTree2 = tree.subString(2, 8);
    cout << "Structure of the tree: " << subStringTree2.toStringPreOrder() << endl;
    cout << "sTRING: " << subStringTree2.toString() << endl;
    cout << "[t] - " << subStringTree2.get(5) << endl;
    cout << "[4] - " << subStringTree2.indexOf('_') << endl;

    cout << "-> Now we reverse substring (2->8) tree" << endl;
    ConcatStringTree reversed2 = subStringTree2.reverse();
    cout << "Structure of the tree: " << reversed2.toStringPreOrder() << endl;

    cout << "-> Now we create a complex tree (different hierarchy between subtrees)" << endl;
    ConcatStringTree s5("_Assignment");
    ConcatStringTree complexTree = tree.concat(s5);
    cout << "Structure of the tree: " << complexTree.toStringPreOrder() << endl;
    cout << "sTring: " << complexTree.toString() << endl;
    cout << "Index of 'n' = " << complexTree.indexOf('n') << endl;
    cout << "Index of 'm' = " << complexTree.indexOf('m') << endl;

    cout << "-> Create of substring (12->27) of the above complex tree" << endl;
    ConcatStringTree reverseComplex = complexTree.subString(12, 27);
    cout << "Structure of the tree: " << reverseComplex.toStringPreOrder() << endl;
}

int main()
{
    // test1();
    /*****************************************************************************/
    // ConcatStringTree sA("Hello"), sB(",_t"), sC("his_is"), sD("_an");
    // ConcatStringTree s1 = sA.concat(sB), s2 = sC.concat(sD), s3 = s1.concat(s2);

    // cout<<"s1 = "<<s1.toStringPreOrder()<<endl;
    // cout<<"s2 = "<<s2.toStringPreOrder()<<endl;
    // cout<<"s3 = "<<s3.toStringPreOrder()<<endl;

    // ConcatStringTree s4 = s3.subString(1,10);

    // cout<<"s4 = "<<s4.toStringPreOrder()<<endl;

    // ConcatStringTree s5 = s4.reverse();
    // cout<<"s5 = "<<s5.toStringPreOrder()<<endl;
    /*******************************************************************************/
    // ConcatStringTree sA("ABC"), sB("DEF"), sC("GHI");

    // ConcatStringTree s1 = sA.concat(sB); // ABCDEF

    // ConcatStringTree s2 = sB.concat(sC); // DEFGHI

    // ConcatStringTree s3 = s1.concat(s2); // ABCDEFDEFGHI

    // ConcatStringTree s4 = s3.subString(1, s3.length()-1);

    // ConcatStringTree s5 = s3.reverse();

    // cout << s4.toString() << endl; // BCDEFDEFGH

    // cout << s5.toString() << endl; // IHGFEDFEDCBA
    /***********************************************************************************/
    // ConcatStringTree s1("Hello");
    // ConcatStringTree s2(",_t");
    // ConcatStringTree s3("his_is");
    // ConcatStringTree s4("_an");

    // ConcatStringTree subtree1 = s1.concat(s2);
    // ConcatStringTree subtree2 = s3.concat(s4);
    // ConcatStringTree tree = subtree1.concat(subtree2);
    // cout << tree.getParTreeStringPreOrder("lll");
    /*************************************************************************************/
    // ConcatStringTree s1("Hello");
    // cout << "Please focus to id: " << s1.getParTreeStringPreOrder("") << endl;
    // ConcatStringTree s2("an-nyeong-ha-se-yo");
    // cout << "Please focus to id: " << s2.getParTreeStringPreOrder("") << endl;
    // ConcatStringTree s3("nee how");
    // cout << "Please focus to id: " << s3.getParTreeStringPreOrder("") << endl;

    // ConcatStringTree s1("abc");          // id = 1
    // ConcatStringTree s2("def");          // id = 2
    // ConcatStringTree s3("ghj");          // id = 3
    // ConcatStringTree s4 = s1.concat(s2); // id = 4
    // ConcatStringTree s5 = s1.concat(s2).concat(s3);
    // cout << "id of s1: " << s1.root->id << endl;
    // cout << "id of s2: " << s2.root->id << endl;
    // cout << "id of s3: " << s3.root->id << endl;
    // cout << "id of s4: " << s4.root->id << endl;
    // cout << "id of s5: " << s5.root->id << endl;

    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0.75,
        2,
        4);
    LitStringHash *litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree *s1 = new ReducedConcatStringTree("a", litStringHash);
    ReducedConcatStringTree *s2 = new ReducedConcatStringTree("bb", litStringHash);

    cout << s1->toString() << endl;
    cout << s2->toString() << endl;
    ReducedConcatStringTree *s3 = new ReducedConcatStringTree("bb", litStringHash);

    cout << litStringHash->getLastInsertedIndex() << endl;
    cout << litStringHash->toString() << endl;
    // delete s3;
    // delete s1;
    // delete s2;
    // delete litStringHash;
}
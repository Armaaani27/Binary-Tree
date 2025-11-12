/*
Armani Ruiz
arj22c
Xian Mallory, COP4530
Assignment 3
*/

#include <iostream>
#include <string>
#include <initializer_list>
using namespace std;

class BET
{
    private:
        struct BinaryNode
        {
            string element;
            BinaryNode *left;
            BinaryNode *right;

            BinaryNode(const string & theElement, BinaryNode *lt, BinaryNode *rt)
                : element{theElement}, left{lt}, right{rt} {}
            BinaryNode(string && theElement, BinaryNode *lt, BinaryNode *rt)
                : element{std::move(theElement)}, left{lt}, right{rt} {}
        };
    
        BinaryNode *root;
        void printInfixExpression(BinaryNode *n) const;
        void makeEmpty(BinaryNode* &t);
        BinaryNode * clone(BinaryNode* t) const;
        void printPostfixExpression(BinaryNode *n) const;
        size_t size(BinaryNode *t) const;
        size_t leaf_nodes(BinaryNode *t) const;

    public:
        BET();
        BET(const string& postfix); // one parameter constructor
        BET(const BET& rhs); // copy constructor
        ~BET(); // destructor
        bool buildFromPostfix(const string& postfix);
        const BET & operator= (const BET &); // assignment operator
        void printInfixExpression() const;
        void printPostfixExpression() const;
        size_t size() const;
        size_t leaf_nodes() const;
        bool empty() const;
};

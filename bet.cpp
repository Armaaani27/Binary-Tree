#include <iostream>
#include <stack>
#include <string>
#include "bet.h"
using namespace std;

/* BET */

// PUBLIC

// default constructor
BET::BET()
{
    root = nullptr;
}

// one parameter constructor
BET::BET(const string& postfix)
{
    root = nullptr;
    buildFromPostfix(postfix);
}

// copy constructor
BET::BET(const BET &rhs)
{
    root = clone(rhs.root);
}

// destructor
BET::~BET()
{
    makeEmpty(root);
}

bool BET::buildFromPostfix(const string& postfix)
{
    stack<BinaryNode*> s;

    // iterate through the postfix string
    size_t i = 0;
    while (i < postfix.length())
    {
        // if character is a number or letter (operand)
        if (isalnum(postfix[i]))
        {
            string newNum = "";
            // this while loop accounts for numbers with multiple digits
            while (isalnum(postfix[i]))
            {
                newNum += postfix[i];
                i++;
            }
            // creates a new leaf node with the resulting number and pushes it onto the stack
            BinaryNode * newNode = new BinaryNode(newNum, nullptr, nullptr);
            s.push(newNode);
        }
        // if character is an operator
        else if (postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '+' || postfix[i] == '-')
        {
            // ensure there are at least two elements to pop
            if(s.size() < 2)
            {
                cout << "Cannot build the tree based on " << postfix << "\n";
                return false;
            }
            string newOperator = {postfix[i]};
            BinaryNode* element1 = s.top();
            s.pop();
            BinaryNode* element2 = s.top();
            s.pop();
            // creates new binary node with the operator as parent and two popped elements as children and pushes it onto the stack
            BinaryNode* newNode = new BinaryNode(newOperator, element2, element1);
            s.push(newNode);
            i++;
        }
        else
        {
            i++;
        }
    }

    // there should be exactly one element left in the stack: the root
    if (s.size() != 1)
    {
        cout << "Cannot build the tree based on " << postfix << "\n";
        return false;
    }

    // final expression at top of stack
    root = s.top();
    return true;
}

const BET& BET::operator=(const BET& rhs)
{
    makeEmpty(root);
    root = clone(rhs.root);
    return *this;
}

void BET::printInfixExpression() const
{
    printInfixExpression(root);
    cout<<endl;
}

void BET::printPostfixExpression() const
{
    printPostfixExpression(root);
    cout<<endl;
}

size_t BET::size() const
{
    return size(root);
}

size_t BET::leaf_nodes() const
{
    return leaf_nodes(root);
}

// if root is nullptr, that can only mean the entire tree is empty
bool BET::empty() const
{
    return root == nullptr;
}

// PRIVATE

void BET::printInfixExpression(BinaryNode *n) const
{
    if (n != nullptr)
    {
        bool leftPrecedence = false;
        bool rightPrecedence = false;
        if ((n -> element) == "*" || (n -> element) == "/")
        {
            // if parent has higher precedence than left child...
            if ((n -> left -> element == "+") || (n -> left -> element == "-"))
            {
                leftPrecedence = true;
            }
            // if parent has higher precedence than right child...
            if (n -> right -> element == "+" || n -> right -> element == "-")
            {
                rightPrecedence = true;
            }
            // if parent has same precedence as right child...
            if (n -> right -> element == "*" || n -> right -> element == "/")
            {
                rightPrecedence = true;
            }
        }
        else if ((n -> element) == "+" || (n -> element) == "-")
        {
            // if parent has same precedence as right child...
            if ((n -> right -> element) == "+" || (n -> right -> element) == "-")
            {
                rightPrecedence = true;
            }
        }
        
        // if precedence exists for left subtree, print parentheses
        if (leftPrecedence)
            cout << "( ";
        printInfixExpression(n -> left);
        if (leftPrecedence)
            cout << ") ";
            
        cout << n -> element << " ";

        // if precedence exists for right subtree, print parentheses
        if (rightPrecedence)
            cout << "( ";
        printInfixExpression(n -> right);
        if (rightPrecedence)
            cout << ") ";
    }
}

// deletes allocated memory and sets t to nullptr, uses recursion to do the same for all children
void BET::makeEmpty(BinaryNode * &t)
{
    if (t != nullptr)
    {
        makeEmpty(t -> left);
        makeEmpty(t -> right);
        delete t;
    }
    t = nullptr;
}

// clone subtree using recursion
BET::BinaryNode* BET::clone(BinaryNode *t) const
{
    if (t == nullptr)
    {
        return nullptr;
    }
    else
    {
        return new BinaryNode{t -> element, clone(t->left), clone(t->right)};
    }
}

// prints left subtree followed by right subtree (using recursion), followed by the element at the current node
void BET::printPostfixExpression(BinaryNode *n) const
{
    if (n != nullptr)
    {
        printPostfixExpression(n -> left);
        printPostfixExpression(n -> right);
        cout << n -> element << " ";
    }
}

// uses recursion to determine size
size_t BET::size(BinaryNode *t) const
{
    if (t != nullptr)
    {
        return 1 + size(t -> left) + size(t -> right);
    }
    return 0;
}

// uses recursion to determine number of leaf nodes
size_t BET::leaf_nodes(BinaryNode *t) const
{
    // if node exists but has no children, return 1
    if (t != nullptr && t -> left == nullptr && t -> right == nullptr)
    {
        return 1;
    }
    else if (t != nullptr)
    {
        return leaf_nodes(t -> left) + leaf_nodes(t -> right);
    }
    return 0;
}


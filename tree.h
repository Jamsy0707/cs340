#include<bits/stdc++.h> 
using namespace std;

struct n 
{
   char d;
   n *l;
   n *r;
};

int r(char inputch);
void push(n *tree);
void construct_expression_tree(char *suffix);
void preOrder(n *tree);
void inOrder(n *tree);
void postOrder(n *tree);
void reOrder (char s);

// Cleaned up code, added comments, fixed error in "else if" statement in "int r" function,
// added the reorder function

#include<bits/stdc++.h> 
#include "tree.h"
using namespace std;

int top = -1;
n *a[50];

int r(char inputch) 					// Function to determine if the character is a letter or a symbol
{
   if (inputch == '+' || inputch == '-' || inputch == '*' || inputch== '/')  // Return -1 for symbol
      return (-1);
   else if ((inputch >= 'A' && inputch <= 'Z') || (inputch >= 'a' && inputch <= 'z') || (inputch >= '0' && inputch <= '9'))  // Return 1 for letter or number
      return (1);
   else
      return (-100);					// Returns -100 if the character is neither a known symbol or letter
}

void push(n *tree) 						// Function to push character to the tree
{					
   top++;
   a[top] = tree;
}

n *pop() 								// Function to pop character from the tree
{
   top--;
   return (a[top + 1]);
}

void construct_expression_tree(char *suffix) {  // Function to create tree from postfix
   char s;
   n *newl, *p1, *p2;
   int flag;
   s = suffix[0];

   for (int i = 1; s != 0; i++) {				// Loop continues to the end of the char array
      flag = r(s);								// Checks if the char is valid
      if (flag == 1) {
         newl = new n;
         newl->d = s;
         newl->l = NULL;
         newl->r = NULL;
         push(newl);
      } else {
         p1 = pop();
         p2 = pop();
         newl = new n;
         newl->d = s;
         newl->l = p2;
         newl->r = p1;
         push(newl);
      }
      s = suffix[i];							// Moves to next character
   }
}

void preOrder(n *tree) {				// Function to convert from the tree to prefix
   if (tree != NULL) {
      cout << tree->d;
      preOrder(tree->l);
      preOrder(tree->r);
   }
}

void inOrder(n *tree) {					// Function to convert from the tree to infix
   if (tree != NULL) {
      inOrder(tree->l);
      cout << tree->d;
      inOrder(tree->r);
   }
}

void postOrder(n *tree) {				// Function to convert from the tree to postfix
   if (tree != NULL) {
      postOrder(tree->l);
      postOrder(tree->r);
      cout << tree->d;
   }
}

void reOrder (char s) {					// Function to reorder from the expression tree to the user's choice
	switch(s) {
		case 'a':
			cout << "Pre-fix: ";
			preOrder(a[0]);
			break;
		case 'b':
			cout << "In-fix: ";
			inOrder(a[0]);
			break;
		case 'c':
			cout << "Post-fix: ";
			postOrder(a[0]);
			break;
		default:
			cout << "The input isn't valid." << endl;
	}
	cout << endl << endl;
}
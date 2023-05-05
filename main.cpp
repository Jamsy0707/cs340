// James Sieben 200455325
// CS 340 A1

// Convert code adapted from: https://www.codespeedy.com/c-program-to-convert-infix-to-postfix/
// Tree code adapted from: https://www.tutorialspoint.com/cplusplus-program-to-construct-an-expression-tree-for-a-postfix-expression
// String to char array adapted from: https://www.geeksforgeeks.org/convert-string-char-array-cpp/
// Evaluate expression tree adapted from: https://cppsecrets.com/users/1470411297108971071031171121169711010864103109971051084699111109/C00-Program-to-evaluate-Postfix-notation.php

// Made code more readable, cleaned up unneccessary text, and added comments for clarity
// I also adapted the code so that the sources could work together and added new functions
// Right now, the code only works with variables or single digit positive numbers

#include <iostream> 
#include<bits/stdc++.h> 
#include <cstring>
using namespace std; 


struct n 
{
   char d;
   n *l;
   n *r;
};

stack<int> s;
int top = -1;
n *a[50];


int precedence(char m) 				// gives a value based on order of operations
{ 
  if(m == '^') 
  	return 3; 
  else if(m == '*' || m == '/') 
  	return 2; 
  else if(m == '+' || m == '-') 
    return 1; 

  return 0;
} 

string convert(string temp) 		// converts infix to postfix or postfix to postfix
{ 
  stack<char> s;					// The stack for characters to be pushed to and popped from
  int length = temp.length(); 		// The length of the inputted string
  string ans; 						// Final postfix string

  for(int i = 0; i < length; i++) 
  { 
    if((temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] >= 'A' && temp[i] <= 'Z') || (temp[i] >= '0' && temp[i] <= '9')) // ie. If the char is a letter in the alphabet or a single digit
        ans+=temp[i]; 				// Adds the letter to the postfix string

    else if(temp[i] == '(') 		// Else if the char is ( push it to the stack
        s.push('('); 
        
    else if(temp[i] == ')') 		// Else if the char is ) look for the opening bracket by pushing characters
    { 
      while(s.top() != '(') 		// Push all char up to the opening bracket
      { 
        char c = s.top(); 
        ans += c;
        s.pop();    
      } 

      if(s.top() == '(') 			// When the closing bracket is reached, pop it
      { 
        char c = s.top(); 
        s.pop(); 
      } 
    } 

    else
	{ 
      while(s.empty()==false && precedence(temp[i]) <= precedence(s.top())) 	// While the string isn't empty and the next char in the 
      { 																		// string is not a higher precedence than the top of the stack 
        ans += s.top(); 			// Add the char to the postfix string
        s.pop(); 					// Pop the char after adding it
      } 

      s.push(temp[i]); 				// Push the next char to the stack
    } 
  } 
  
  while(s.empty() == false) 		// Condition for if the string is empty
  { 
    ans += s.top(); 
    s.pop(); 
  } 
  
  return ans;						// Print the completed postfix string
}

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
			cout << endl << "Pre-fix: ";
			preOrder(a[0]);
			break;
		case 'b':
			cout << endl << "In-fix: ";
			inOrder(a[0]);
			break;
		case 'c':
			cout << endl << "Post-fix: ";
			postOrder(a[0]);
			break;
		default:
			cout << endl << "The input isn't valid." << endl;
	}
	cout << endl << endl;
}

void evaluate(string str)
{
    //traversing postfix expression from left to right
    for(int i=0;i<str.length();i++){

        //if symbol is a digit push it in stack
        if (isdigit(str[i]))
            s.push(str[i] - '0');

        //if symbol is an operator then pop top 2 elements from stack, perform specific operation and push the result back into stack
        else{
            int op2=s.top();
            s.pop();
            int op1=s.top();
            s.pop();

            if(str[i]=='+')
                s.push(op1+op2);
            else if(str[i]=='-')
                s.push(op1-op2);
            else if(str[i]=='*')
                s.push(op1*op2);
            else if(str[i]=='/')
                s.push(op1/op2);
        }   
    }
}

int main() 
{ 
  string expression;
  char choice;
  
  cout << "Enter the expression to convert. (No spaces): ";
  cin >> expression;
  cout << "What is the output? (type a for pre-fix, b for in-fix, c for post-fix, or d to evaluate): ";
  cin >> choice;

  string post = convert(expression); 			// Converts the input to postfix

  int n = post.length();						// Finds length of converted string
  char char_array[n + 1];						// Creates a char array to hold the string
  strcpy(char_array, post.c_str());				// Copies the string to the char array

  construct_expression_tree(char_array);		// Creates the tree from postfix

  if (choice != 'd')
  	reOrder (choice);								// Reorders the expression tree to the user's choice
  else
  {
	evaluate(post);								// Evaluates if the user types 'd'
	cout << endl << "The evaluated expression is " << s.top() << endl << endl;
  }

  return 0; 
} 
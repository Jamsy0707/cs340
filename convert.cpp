// Cleaned up code, added comments for visibility

#include<bits/stdc++.h> 
#include "convert.h"
using namespace std; 


int precedence(char m) 
{ 
  if(m == '^') 
  	return 3; 
  else if(m == '*' || m == '/') 
  	return 2; 
  else if(m == '+' || m == '-') 
    return 1; 

  return 0;
} 

string convert(string temp) 			// converts infix to postfix or postfix to postfix
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
// James Sieben 200455325
// CS340 A2 Feb. 28, 2022
// Code partially adapted from wikipedia


#include <iostream>
#include <math.h>
using namespace std;


void BUILDHEAP(int h[]);
void PUSHDOWN(int h[], int i);
void PUSHDOWNMIN(int h[], int i);
void PUSHDOWNMAX(int h[], int i);
void PUSHUP(int h[], int i);
void PUSHUPMIN(int h[], int i);
void PUSHUPMAX(int h[], int i);
int FINDMIN(int h[]);
int FINDMAX(int h[]);

int size = 0;								//Keeps track of the size of the user inputted array

int main() {
	int h[999];								//Declare array filled with 0s
	for (size; size < 999; size++) {
		h[size] = 0;
	}
	
	cout << "Please enter up to 100 integers. Enter 999 to quit." << endl;
	size = 0;
	do {									//Read user input
		cin >> h[size];
		size++;
	} while (h[size-1] != 999);
	h[size] = 0;							//Reset the 999 spot to 0

	BUILDHEAP(h);


	return 0;
}



// Functions for building the heap

void BUILDHEAP(int h[]) {						//Initial function to build heap using bottom up method
    for (int i = size/2; i > 0; i--)
        PUSHDOWN(h, i);
}

void PUSHDOWN(int h[], int i) {					//Determines if the element is a min or a max
    if (i % 2 == 0)
        PUSHDOWNMIN(h, i);
    else
        PUSHDOWNMAX(h, i);
}

void PUSHDOWNMIN(int h[], int i) {				//Pushes down mins to their correct spot
    if (h[2*i+1] != 0) {
		int child1 = 2*i+1;
		int child2 = 2*i+2;
		int grandchild1 = 2*child1+1;
		int grandchild2 = 2*child1+2; 
		int grandchild3 = 2*child2+1; 
		int grandchild4 = 2*child2+2;
		
        int m;									//Declare m as the smallest child or grandchild
		if (h[child1] < h[child2] && h[grandchild1] && h[grandchild2] && h[grandchild3] && h[grandchild4])
			m = child1;
		else if (h[child2] < h[child1] && h[grandchild1] && h[grandchild2] && h[grandchild3] && h[grandchild4])
			m = child2;
		else if (h[grandchild1] < h[child1] && h[child2] && h[grandchild2] && h[grandchild3] && h[grandchild4])
			m = grandchild1;
		else if (h[grandchild2] < h[child1] && h[child2] && h[grandchild1] && h[grandchild3] && h[grandchild4])
			m = grandchild2;
		else if (h[grandchild3] < h[child1] && h[child2] && h[grandchild2] && h[grandchild1] && h[grandchild4])
			m = grandchild3;
		else if (h[grandchild4] < h[child1] && h[child2] && h[grandchild2] && h[grandchild3] && h[grandchild1])
			m = grandchild4;
		
        if (m == grandchild1 || grandchild2 || grandchild3 || grandchild4) { 
            if (h[m] < h[i]) {
				int temp = h[m];					//Swap the two elements so m is in the correct spot
				h[m] = h[i];
				h[i] = temp;
				int parent = floor((m-1)/2);
				
                if (h[m] > h[parent]) {
					temp = h[m];					//Swap the two elements so m is in the correct spot
					h[m] = h[parent];
					h[parent] = temp;
				}
                PUSHDOWNMIN(h, m);
			}
		} else if (h[m] < h[i]) {
            int temp = h[m];
			h[m] = h[i];
			h[i] = temp;
		} 
	}
}

void PUSHDOWNMAX(int h[], int i) {
    if (h[2*i+1] != 0) {
		int child1 = 2*i+1;
		int child2 = 2*i+2;
		int grandchild1 = 2*child1+1;
		int grandchild2 = 2*child1+2; 
		int grandchild3 = 2*child2+1; 
		int grandchild4 = 2*child2+2;

		int m;									//Declare m as the largest child or grandchild
        if (h[child1] > h[child2] && h[grandchild1] && h[grandchild2] && h[grandchild3] && h[grandchild4])
			m = child1;
		else if (h[child2] > h[child1] && h[grandchild1] && h[grandchild2] && h[grandchild3] && h[grandchild4])
			m = child2;
		else if (h[grandchild1] > h[child1] && h[child2] && h[grandchild2] && h[grandchild3] && h[grandchild4])
			m = grandchild1;
		else if (h[grandchild2] > h[child1] && h[child2] && h[grandchild1] && h[grandchild3] && h[grandchild4])
			m = grandchild2;
		else if (h[grandchild3] > h[child1] && h[child2] && h[grandchild2] && h[grandchild1] && h[grandchild4])
			m = grandchild3;
		else
			m = grandchild4;
		
        if (m == grandchild1 || grandchild2 || grandchild3 || grandchild4) {
            if (h[m] > h[i]) {
                int temp = h[m];
				h[m] = h[i];
				h[i] = temp;
				int parent = floor((m-1)/2);
				
                if (h[m] > h[parent]) {					//Swap the two elements so m is in the correct spot
                    temp = h[m];
					h[m] = h[parent];
					h[parent] = temp;
				}
                PUSHDOWNMAX(h, m);
			}
		} else if (h[m] > h[i]) {						//Swap the two elements so m is in the correct spot
            int temp = h[m];
			h[m] = h[i];
			h[i] = temp;
		}
	}
}



// Functions for insertions

void PUSHUP(int h[], int i) {					//Function pushes up elements to make room for an insert
	int parent = floor((i-1)/2);
	int temp;
	
    if (i != 0) {
        if (i % 2 == 0) {
            if (h[i] > h[parent]) {
                temp = h[i];					//Swap i and parent
				h[i] = h[parent];
				h[parent] = temp;
                PUSHUPMAX(h, parent);
			} else 
                PUSHUPMIN(h, i);
		} else {
            if (h[i] < h[parent]) {				//Swap i and parent
                temp = h[i];
				h[i] = h[parent];
				h[parent] = temp;
                PUSHUPMIN(h, parent);
			} else {
                PUSHUPMAX(h, i);
			}
		}
	}
}

void PUSHUPMIN(int h[], int i) {				//Helper to PUSHUP if node is a min
	int parent = floor((i-1)/2);
	int grandparent = floor((parent-1)/2);

    if ((grandparent != parent) && (h[i] < h[grandparent])) {
        int temp = h[i];
		h[i] = h[grandparent];
		h[grandparent] = temp;
        PUSHUPMIN(h, grandparent);
	}
}

void PUSHUPMAX(int h[], int i) {				//Helper to PUSHUP if node is a max
	int parent = floor((i-1)/2);
	int grandparent = floor((parent-1)/2);

    if ((grandparent != parent) && (h[i] > h[grandparent])) {
        int temp = h[i];
		h[i] = h[grandparent];
		h[grandparent] = temp;
        PUSHUPMAX(h, grandparent);
	}
}



// FindMin and FindMax
int FINDMIN(int h[]) {							//Returns the root node
	return h[0];
}

int FINDMAX(int h[]) {							//Returns the largest node (either in position 1 or 2)
	int max;
	if (h[1] > h[2])
		max = h[1];
	else
		max = h[2];
	return max;
}
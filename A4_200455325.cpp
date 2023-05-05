// James Sieben
// 200455325
// Cs 340 A4


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Final puzzle state
const int GOAL_STATE[3][3] =
{
    {1, 2, 3},
    {8, 0, 4},
    {7, 6, 5}
};

// Function compares two boards to determine equality
bool compareStates(const int a[3][3], const int b[3][3])
{
    bool same = true;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            if (a[i][j] != b[i][j])
            {
                same = false;
                break;
            }

        if (same == false)
            break;
    }

    return same;
}

// Holds the current state                             
struct Puzzle
{
    int grid[3][3];

    // Values are used in the best first search algos
    int depth = 0;
    int score = 0;

    // Keeps a record of what moves have been made
    vector<Puzzle> ancestors;

    // Initializes the grid to all 0s
    Puzzle()
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                grid[i][j] = 0;
    }

    // Changes puzzle grid to user input
    Puzzle(int new_grid[3][3])
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                grid[i][j] = new_grid[i][j];
            }
        }
    }

    // Defines == for use of comparisons between states
    bool operator==(const Puzzle& p)
    {
        return (compareStates(this->grid, p.grid));
    }

    // Defines < for use of sorting
    bool operator<(const Puzzle& p)
    {
        return (this->score < p.score);
    }

    // Function prints the grid
    void printGrid()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << grid[i][j] << " ";
            }

            cout << endl;
        }
    }
};

// Returns a new puzzle state in which the empty space has been moved in the specified direction
Puzzle move(Puzzle node, string dir)
{
    int temp;

    int zero_i;
    int zero_j;

    // Finding empty position (denoted by 0) on the board
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (node.grid[i][j] == 0)
            {
                zero_i = i;
                zero_j = j;
            }
        }
    }

    // Executing movement
    if (dir == "up")
    {
        temp = node.grid[zero_i - 1][zero_j];

        node.grid[zero_i - 1][zero_j] = 0;
        node.grid[zero_i][zero_j] = temp;
    }
    else if (dir == "down")
    {
        temp = node.grid[zero_i + 1][zero_j];

        node.grid[zero_i + 1][zero_j] = 0;
        node.grid[zero_i][zero_j] = temp;
    }
    else if (dir == "left")
    {
        temp = node.grid[zero_i][zero_j - 1];

        node.grid[zero_i][zero_j - 1] = 0;
        node.grid[zero_i][zero_j] = temp;
    }
    else if (dir == "right")
    {
        temp = node.grid[zero_i][zero_j + 1];

        node.grid[zero_i][zero_j + 1] = 0;
        node.grid[zero_i][zero_j] = temp;
    }
    else
    {
        cout << "Error: Invalid move attempted." << endl;
    }

    return node;
}

// Returns true if a move in the specified direction is possible on the specified game state
bool canMove(Puzzle node, string dir)
{
    int zero_i;
    int zero_j;

    // Finding empty space on board
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (node.grid[i][j] == 0)
            {
                zero_i = i;
                zero_j = j;
            }
        }
    }

    // Checking illegal moves
    if (dir == "up" && zero_i == 0)
    {
        return false;
    }
    else if (dir == "down" && zero_i == 2)
    {
        return false;
    }
    else if (dir == "left" && zero_j == 0)
    {
        return false;
    }
    else if (dir == "right" && zero_j == 2)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Used for printing the solution in depth first search
void printVisited(vector<Puzzle> visited)
{
    for (int i = 0; i < visited.size(); i++)
    {
        visited[i].printGrid();

        cout << endl;
    }
}

// Prints the solution for other algorithms
void printSolution(Puzzle node)
{
    for (int i = 0; i < node.ancestors.size(); i++)
    {
        node.ancestors[i].printGrid();
        cout << endl;
    }

    node.printGrid();
    cout << endl;
}

// Function for DFS algorithm
void depthFirstSearch(Puzzle node, int max_iter)
{
    // Frontier acts as a stack to hold states that need to be checked
    vector<Puzzle> frontier;

    // Once a move has been checked, it is added here so that no states are checked twice
    vector<Puzzle> visited;

    // Possible moves from each state are stored here
    vector<Puzzle> possible_moves;

    int states_visited = 0;
    int nodes_generated = 0;

    frontier.push_back(node);

    while (!frontier.empty() && states_visited < max_iter)
    {
        states_visited++;

        node = frontier.back();
        frontier.pop_back();

        node.printGrid();
        cout << endl;

        visited.push_back(node);

        // If the node we're currently checking is the goal state, we can print the solution and exit the function
        if (compareStates(node.grid, GOAL_STATE))
        {
            cout << "Goal state found. Solution:" << endl << endl;
            printVisited(visited);
            cout << states_visited << " states visited. " << nodes_generated << " nodes generated." << endl;
            return;
        }

        // Checking what moves are possible from this state
        if (canMove(node, "up"))
        {
            possible_moves.push_back(move(node, "up"));
        }

        if (canMove(node, "down"))
        {
            possible_moves.push_back(move(node, "down"));
        }

        if (canMove(node, "left"))
        {
            possible_moves.push_back(move(node, "left"));
        }

        if (canMove(node, "right"))
        {
            possible_moves.push_back(move(node, "right"));
        }

        for (int i = 0; i < possible_moves.size(); i++)
        {
            // If a possible move hasn't already been visited and isn't already in the frontier, add it to the frontier
            if (find(visited.begin(), visited.end(), possible_moves[i]) == visited.end() && find(frontier.begin(), frontier.end(), possible_moves[i]) == frontier.end())
            {
                frontier.push_back(possible_moves[i]);
                nodes_generated++;
            }
        }

        // Clear possible moves for next iteration
        possible_moves.clear();
    }

    // If frontier is emptied (no more possible states to check) or the max. iterations is reached, the solution was not found.
    cout << "Solution not found. " << states_visited << " states visited. " << nodes_generated << " nodes generated." << endl;
    return;
}

//Function for BFS algorithm
void breadthFirstSearch(Puzzle node, int max_iter)
{
    vector<Puzzle> frontier;
    vector<Puzzle> visited;
    vector<Puzzle> possible_moves;

    int states_visited = 0;
    int nodes_generated = 0;

    frontier.push_back(node);

    while (!frontier.empty() && states_visited < max_iter)
    {
        states_visited++;

        // Instead of checking from back, check from front
        node = frontier.front();
        frontier.erase(frontier.begin());

        node.printGrid();
        cout << endl;

        visited.push_back(node);

        if (compareStates(node.grid, GOAL_STATE))
        {
            cout << "Goal state found. Solution:" << endl << endl;
            printSolution(node);
            cout << states_visited << " states visited. " << nodes_generated << " nodes generated." << endl;
            return;
        }

        if (canMove(node, "up"))
        {
            possible_moves.push_back(move(node, "up"));
        }

        if (canMove(node, "down"))
        {
            possible_moves.push_back(move(node, "down"));
        }

        if (canMove(node, "left"))
        {
            possible_moves.push_back(move(node, "left"));
        }

        if (canMove(node, "right"))
        {
            possible_moves.push_back(move(node, "right"));
        }

        for (int i = 0; i < possible_moves.size(); i++)
        {
            if (find(visited.begin(), visited.end(), possible_moves[i]) == visited.end() && find(frontier.begin(), frontier.end(), possible_moves[i]) == frontier.end())
            {
                frontier.push_back(possible_moves[i]);

                // Using ancestors array to store solution
                frontier.back().ancestors.push_back(node);

                nodes_generated++;
            }
        }

        possible_moves.clear();
    }

    cout << "Solution not found. " << states_visited << " states visited. " << nodes_generated << " nodes generated." << endl;
    return;
}

// Returns number of tiles in the wrong spot
int getMisplacedTiles(Puzzle node)
{
    int misplaced_tiles = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (node.grid[i][j] != GOAL_STATE[i][j])
            {
                misplaced_tiles++;
            }
        }
    }

    return misplaced_tiles;
}

// Returns the coordinates of a tile
vector<int> findOnGrid(const int grid[3][3], int search)
{
    vector<int> coords;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] == search)
            {
                coords.push_back(i);
                coords.push_back(j);

                return coords;
            }
}

// Calculates and returns the manhattan distance
int getManhattanDist(const int gridA[3][3], const int gridB[3][3])
{
    int total = 0;

    vector<int> coordsA;
    vector<int> coordsB;

    for (int i = 0; i < 9; i++)
    {
        coordsA = findOnGrid(gridA, i);
        coordsB = findOnGrid(gridB, i);

        total += abs(coordsA[0] - coordsB[0]) + abs(coordsA[1] - coordsB[1]);
    }
    
    return total;
}

// Returns the coordinates for the next clockwise tile
vector<int> getNextCoords(vector<int> coords)
{
    vector<int> next_coords;

    if (coords[0] == 0 && coords[1] == 0)
    {
        next_coords.push_back(0);
        next_coords.push_back(1);

        return next_coords;
    }
    else if (coords[0] == 0 && coords[1] == 1)
    {
        next_coords.push_back(0);
        next_coords.push_back(2);

        return next_coords;
    }
    else if (coords[0] == 0 && coords[1] == 2)
    {
        next_coords.push_back(1);
        next_coords.push_back(2);

        return next_coords;
    }
    else if (coords[0] == 1 && coords[1] == 2)
    {
        next_coords.push_back(2);
        next_coords.push_back(2);

        return next_coords;
    }
    else if (coords[0] == 2 && coords[1] == 2)
    {
        next_coords.push_back(2);
        next_coords.push_back(1);

        return next_coords;
    }
    else if (coords[0] == 2 && coords[1] == 1)
    {
        next_coords.push_back(2);
        next_coords.push_back(0);

        return next_coords;
    }
    else if (coords[0] == 2 && coords[1] == 0)
    {
        next_coords.push_back(1);
        next_coords.push_back(0);

        return next_coords;
    }
    else
    {
        next_coords.push_back(0);
        next_coords.push_back(0);

        return next_coords;
    }
}

// Returns the sequence score of a state
int getSequenceScore(Puzzle node)
{
    int total = 0;
    int j = 0;

    vector<int> coords;
    vector<int> next_coords;

    for (int i = 0; i < 9; i++)
    {
        coords = findOnGrid(node.grid, i);

        if (coords[0] == 1 && coords[1] == 1)
        {
            total += 1;
        }
        else
        {
            j = i + 1;

            if (j == 9)
            {
                j = 1;
            }

            next_coords = getNextCoords(coords);
            
            if (!(findOnGrid(node.grid, j)[0] == next_coords[0] && findOnGrid(node.grid, j)[1] == next_coords[1]))
            {
                total += 2;
            }
        }
    }

    return total;
}

// Used by best first search to determine which heuristic to use
int getScore(Puzzle node, string heuristic)
{
    if (heuristic == "A")
    {
        return node.depth + getMisplacedTiles(node);
    }
    else if (heuristic == "B")
    {
        return node.depth + getManhattanDist(node.grid, GOAL_STATE);
    }
    else if (heuristic == "C")
    {
        return node.depth + getManhattanDist(node.grid, GOAL_STATE) + 3 * getSequenceScore(node);
    }
}

// Main best first search function
void bestFirstSearch(Puzzle node, int max_iter, string heuristic)
{
    vector<Puzzle> frontier;
    vector<Puzzle> visited;
    vector<Puzzle> possible_moves;

    int states_visited = 0;
    int nodes_generated = 0;

    frontier.push_back(node);

    while (!frontier.empty() && states_visited < max_iter)
    {
        states_visited++;

        node = frontier.front();
        frontier.erase(frontier.begin());

        node.printGrid();
        cout << endl;
        cout << "Depth: " << node.depth << endl;
        cout << "Score: " << node.score << endl;
        cout << endl;

        visited.push_back(node);

        if (compareStates(node.grid, GOAL_STATE))
        {
            cout << "Goal state found. Solution:" << endl << endl;
            printSolution(node);
            cout << states_visited << " states visited. " << nodes_generated << " nodes generated." << endl;
            return;
        }

        if (canMove(node, "up"))
        {
            possible_moves.push_back(move(node, "up"));
        }

        if (canMove(node, "down"))
        {
            possible_moves.push_back(move(node, "down"));
        }

        if (canMove(node, "left"))
        {
            possible_moves.push_back(move(node, "left"));
        }

        if (canMove(node, "right"))
        {
            possible_moves.push_back(move(node, "right"));
        }

        for (int i = 0; i < possible_moves.size(); i++)
        {
            // Incrementing depth and calculating score of move
            possible_moves[i].depth = node.depth + 1;
            possible_moves[i].score = getScore(possible_moves[i], heuristic);

            if (find(visited.begin(), visited.end(), possible_moves[i]) == visited.end() && find(frontier.begin(), frontier.end(), possible_moves[i]) == frontier.end())
            {
                frontier.push_back(possible_moves[i]);
                frontier.back().ancestors.push_back(node);
                nodes_generated++;
            }
        }

        // Sorting the frontier by score, making it function as a priority queue
        sort(frontier.begin(), frontier.end());
        possible_moves.clear();
    }

    cout << "Solution not found. " << states_visited << " states visited. " << nodes_generated << " nodes generated." << endl;
    return;
}



int main()
{
    int grid[3][3];
    int max_iter;
    char search_selection;

    cout << "Please enter 9 numbers representing the board in row-major order." << endl
		 << "Ex: 123804765 is the goal board." << endl;
	string userInput;
	cin >> userInput;

    //Convert the user string to a 2d array
	for (int row = 0; row < 3; row++)
	{
		for (int  col = 0; col < 3; col++)
		{
			grid[row][col] = userInput[row * 3 + col] - 48;
		}
	}

    Puzzle initial(grid);

    cout << endl << "Input the value for max. iterations: ";
    cin >> max_iter;

    cout << endl;
    cout << "Choose a search algorithm:" << endl;
    cout << "   A) Depth-first search" << endl;
    cout << "   B) Breadth-first search" << endl;
    cout << "   C) Best-first search with heuristic depth + out of place tiles" << endl;
    cout << "   D) Best-first search with heuristic depth + min. moves to goal" << endl;
    cout << "   E) Best-first search with heuristic depth + H" << endl;
    cout << endl;

    cin >> search_selection;
    cout << endl;

    switch (search_selection)
    {
    case 'A' | 'a':
        cout << "You selected: Depth First Search" << endl << endl;
        depthFirstSearch(initial, max_iter);
        break;

    case 'B' | 'b':
        cout << "You selected: Breadth First Search" << endl << endl;
        breadthFirstSearch(initial, max_iter);
        break;

    case 'C' | 'c':
        cout << "You selected: Best First Search with heuristic depth + out of place tiles" << endl << endl;
        bestFirstSearch(initial, max_iter, "A");
        break;

    case 'D' | 'd':
        cout << "You selected: Best First Search with heuristic depth + min. moves to goal" << endl << endl;
        bestFirstSearch(initial, max_iter, "B");
        break;

    case 'E' | 'e':
        cout << "You selected: Best First Search with heuristic depth + H" << endl << endl;
        bestFirstSearch(initial, max_iter, "C");
        break;
        
    default:
        cout << "Your input is not valid." << endl << endl;
    }

	return 0;
}
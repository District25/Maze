#include "maze.h"
#include <QDebug>
#include <random>
#include <ctime>
#include <stack>

// Default constructor
Maze::Maze(){
    /*grid = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1},
        {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    initRobotPosition = placeRobotRandomly();
    robotPosition = initRobotPosition;*/
}

// Parameter constructor
Maze::Maze(int rows, int col)
{
    robotPosition = (1, 1); // Initial robot position
    // Grid is initialy filled with walls (1)
    grid = std::vector<std::vector<int>>(rows, std::vector<int>(col, 1));
}

// Generate a random Maze with stack
void Maze::generateMaze(int rows, int cols)
{
    // Grid is initialy filled with walls (1)
    grid = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 1));

    std::stack<Coord> stack;
    stack.push(Coord(1, 1)); // Starting point
    grid[1][1] = 0;

    std::mt19937 rng(std::random_device{}());

    while (!stack.empty()) {
        Coord current = stack.top();

        std::vector<Coord> directions = {
            {2, 0}, {-2, 0}, {0, 2}, {0, -2}
        };
        std::shuffle(directions.begin(), directions.end(), rng);

        bool moved = false;
        for (const Coord& dir : directions) {
            int nx = current.x + dir.x;
            int ny = current.y + dir.y;

            if (nx > 0 && nx < cols - 1 && ny > 0 && ny < rows - 1 && grid[ny][nx] == 1) {
                // Remove the walls between the cells
                grid[current.y + dir.y / 2][current.x + dir.x / 2] = 0;
                grid[ny][nx] = 0;

                stack.push(Coord(nx, ny));
                moved = true;
                break;
            }
        }

        if (!moved) {
            stack.pop(); // No possible move → backtrack
        }
    }
    // Call the function to add an exit where it is possible
    placeExit(rows, cols);
}

// Place the robot in any free cells of the maze randomly
Coord Maze::placeRobotRandomly() const
{
    std::vector<Coord> freeCells;

    for (int y = 0; y < getRows(); ++y) {
        for (int x = 0; x < getCol(); ++x) {
            if (grid[y][x] == 0) {
                freeCells.emplace_back(x, y);
            }
        }
    }

    if (freeCells.empty()) {
        return Coord(0, 0); // fallback
    }

    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<size_t> dist(0, freeCells.size() - 1);

    return freeCells[dist(rng)];
}

// Return true if cell is anything but a wall
bool Maze::isCellFree(int x, int y) const
{
    return grid[y][x] == 0 || Coord(x, y) == getRobotPosition() || Coord(x, y) == getExitPosition();
}

// Move robot to the next position
void Maze::moveRobot(Coord next){ robotPosition = next; }

// Return the robot current position
Coord Maze::getRobotPosition() const { return robotPosition; }

// Return the exit position
Coord Maze::getExitPosition() const { return exitPosition; }

// Return the initial robot position
Coord Maze::getInitRobotPosition() const { return initRobotPosition; }

std::vector<std::vector<int> > Maze::getGrid() { return grid; }

// Set the robot position
void Maze::setRobotPosition(Coord pos) { robotPosition = pos; }

// Set the variable that allows me to know if a maze has beeen generated
void Maze::setGenerated(bool state){ generated = state; }

// Return true if robot found the exit
bool Maze::hasWon(){ return Win; }

void Maze::placeExit(int rows, int cols)
{
    // Place an exit on the end of the maze
    for (int y = rows - 2; y > 0; y--) {
        for (int x = cols - 2; x > 0; x--) {
            if (grid[y][x] == 0) {
                grid[y][x] = 2;
                exitPosition = Coord(x, y);
                return;
            }
        }
    }
}

// Add an observer to the list
void Maze::subscribe(Observer* o) { observers.push_back(o); }

// Notify observers of changes
void Maze::notifyObservers() {
    for (Observer* o : observers) {
        o->update();
    }
}

// Return the # of rows in the maze
int Maze::getRows() const{ return grid.size();}

// Return the # of cols in the maze
int Maze::getCol() const{ return grid[0].size();}

bool Maze::getGenerated() const { return generated; }

// Set Winning state after finding the exit with robot
void Maze::setWin(bool state){ Win = state; }

// Set the grid attribute
void Maze::setGrid(const std::vector<std::vector<int> > &newGrid) { grid = newGrid; }

#ifndef HEADER_FILE
#define HEADER_FILE
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
using namespace std;

void printBoard();
void startNewGame();
void generateRandomTile();
bool checkIfEqual(vector<vector<int>> arr1, vector<vector<int>> arr2, int numRows, int numCols);
void copy(vector<vector<int>> &b1, vector<vector<int>> b2, int numRows, int numCols);
void set(int rowNum, int colNum, int val);
vector<vector<int>> getEmptyTiles();
bool emptySlotLeft();
void addRandomTile(int numTimes);
vector<vector<int>> getBoard();
void generateRandomMove();
void addTileValue(int row, int col, int val);
int getTileValue(int row, int col);
vector<string> getNames(int row, int col);
string getBoardState();
void assignName(string name, int row_, int col_);
bool moveRight(int numRows, int numCols, int op);
bool moveLeft(int numRows, int numCols, int op);
bool moveDown(int numRows, int numCols, int op) ;
bool moveUp(int numRows, int numCols, int op);
void move(int moveDirection, int op) ;
#endif 
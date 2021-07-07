#include<string.h>
#include <bits/stdc++.h>
#include "parser.tab.hpp"
#include "header.h"
using namespace std;

vector<vector<int>> board;
vector<vector<int>> previousState;
map<pair<int, int>, vector<string>> names;
int type = 1;
int rows = 4;
int cols = 4;
void deleteName(string name){
	pair<int, int> p1 = make_pair(-1, -1);
	for (auto i:names){
		vector<string> temp = i.second;
		if(temp.size() == 1){
				if(temp[0] == name){
					p1 = i.first;
					break;
				}
		}
		for(auto it = temp.begin(); it!=temp.end(); it++){
			if(*it == name){
					//names[i.first].erase(it);
					temp.erase(it);
					names[i.first] = temp;
					break;
				}
		}
		if(p1.first>=0) break;
	}
	if(p1.first>=0) names.erase(p1);
}
void assignName(string name, int row_, int col_){
	
    vector<string> v1;
	v1.push_back(name);
	//Check if the name is already there. 
	deleteName(name);
    if(names.find(make_pair(row_, col_))== names.end()){
        names[make_pair(row_,col_)] = v1;
    }
    else{
        names[make_pair(row_, col_)].push_back(name);
    }
    printf("Name assigned successfully\n");
}
vector<string> getNames(int row, int col){
    pair<int, int> p1 = make_pair(row, col);
    vector<string> v;
    if(names.find(p1) != names.end()){
        v = names[p1];
    }
    return v;
}
string getBoardState(){
	string b;
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			b.append(to_string(board[i][j]));
			b.append(" ");
		}
	}
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			if(names.find(make_pair(i,j)) != names.end()){
				vector<string> x;
				vector<string> vecs(names[make_pair(i,j)].begin(),names[make_pair(i,j)].end());
				b.append(to_string(i+1));
				b.append(",");
				b.append(to_string(j+1));

				for(int i = 0; i<vecs.size(); i++){
					b.append(vecs[i]);
					if(i != vecs.size()-1)
						b.append(",");
				}
				b.append(" ");
			}
		}
	}
	cout<<"\n";
	return b;
}
void addTileValue(int row, int col, int val){
    board[row][col] = val;
	if(val == 0){
		if(names.find(make_pair(row, col)) != names.end()){
			names.erase(make_pair(row, col));
		}
	}
}

void printLine(int n){
    for(int i = 0; i<n; i++)
    {
        cout<<"-";
    }
    cout<<"\n";
}
void printBoard(){
	cout<<"\n";
    printLine(16);
    for(int i = 0; i<4; i++){
        cout<<"| ";
        for(int j = 0; j<4; j++){
            cout<<board[i][j]<<" | ";

        }
        cout<<"\n";
        printLine(16);
    }
}

void startNewGame() {
	//generate two random tiles
    generateRandomTile();
	printBoard();

}
void generateRandomTile() {
	addRandomTile(1);
}

void changeNegativeToZero(){
	for(int i = 0; i<4; i++)
	{
		for(int j = 0; j<4; j++){
			if(board[i][j]<0){
				board[i][j] = 0;
			}
		}
	}
}
bool checkIfEqual(vector<vector<int>> arr1, vector<vector<int>> arr2, int numRows, int numCols) {
		for(int i = 0; i<numRows; i++) {
			for(int j = 0; j<numCols; j++) {
				if(arr1[i][j]!=arr2[i][j])
					return false;
			}
		}
		return true;
	}
void copy(vector<vector<int>> &b1, vector<vector<int>> b2, int numRows, int numCols) {
		for(int i = 0; i<numRows; i++) {
			for(int j = 0; j<numCols; j++) {
				b1[i][j] = b2[i][j];
			}
		}
		
}

int getTileValue(int row, int col){
    return board[row-1][col-1];
}

vector<vector<int>> getEmptyTiles() {
	vector<vector<int>> emptyTileIndex;
	for (int i=0;i<rows;i++){
			for (int j=0;j<cols;j++){
				vector<int> ind;
				if (board[i][j]==0){
						ind.push_back(i);
						ind.push_back(j);
						emptyTileIndex.push_back(ind);
				}
			}
	}
	return emptyTileIndex;
}

bool emptySlotLeft() {
		for(int i = 0; i<rows; i++) {
			for(int j = 0; j<cols; j++) {
				if(board[i][j] == 0) {
					return true;
				}
			
			}
		}
		return false;			
}

void addRandomTile(int numTimes) {
		while(numTimes>0) {
		if(emptySlotLeft()) {
			//Generate random tile. 
			vector<vector<int>> emptyTiles = getEmptyTiles();
			//The random number should be either 2 or 4. 
			int randomNumber = (int) (rand()%5);
			if(randomNumber<3) randomNumber = 2;
			else randomNumber = 4;
			vector<int> tile = emptyTiles[(int)(rand()%emptyTiles.size())];
            // cout<<"tILE INDEX "<<tile[0]<<tile[1]<<"\n";
			board[tile[0]][tile[1]] = randomNumber;
		}
		numTimes--;
		}
}


void generateRandomMove() {
	int i = 0;
	
	while(checkIfEqual(previousState, board, 4, 4)) {
	if(i>0) {
		cout << "Invalid move\n";
	}
	int randomNumber = (int) (rand()*4.0);
	move(randomNumber);
	printBoard();
	//System.out.print("The random move generated is"+ randomNumber+ "\n");
	i++;
	}
}

void addName(pair<int, int> p1, pair<int, int> p2){
    //Add names of p2 to p1. 
    vector<string> tempNames;
    if(names.find(p2)!=  names.end() ){
        tempNames = names[p2];
        names.erase(p2);
                    
    }
    if(names.find(p1) !=names.end()){
        vector<string> temp = names[p1];
        names[p1].insert(names[p1].end(), tempNames.begin(), tempNames.end());
		
    }
	else{
		if(tempNames.size()>0)
			names[p1] = tempNames;
	}
    

}
bool moveRight(int numRows, int numCols, int op) {
	vector<vector<int>> tempBoard{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	copy(tempBoard, board, numRows, numCols);
		
	
		
    for(int i = 0; i<numRows; i++) {
		//Left. 
		int j = 0;
		int  k = j+1;
		while(j<numCols-1 && k<numCols ) {
			if(board[numRows-i-1][numCols-j-1] == 0) {
				
				j++;
				if(j >= k)
					k++;
			}
			else if(board[numRows-i-1][numCols-k-1]==0) {
				k++;
			}
			else if(board[numRows-i-1][numCols-j-1] == board[numRows-i-1][numRows-1-k]) {
				
                 if(op == 0)
				    board[numRows-i-1][numCols-j-1]= board[numRows-i-1][numCols-j-1]*board[numRows-i-1][numCols-j-1];
                if(op == 1)
                    board[numRows-i-1][numCols-j-1] = 1;
                if(op == 2){
					if(type == 1)
                    	board[numRows-i-1][numCols-j-1] = 0;
					if(type == 2)
						board[numRows-i-1][numCols-j-1] = -1;
					
				}
                if(op == 3)
                    board[numRows-i-1][numCols-j-1]*= 2;
				board[numRows-i-1][numCols-k-1] = 0;
                
                addName(make_pair(numRows-i-1,numCols-j-1), make_pair(numRows-i-1,numCols-k-1));
				if(op == 2){
					addTileValue(numRows-i-1, numCols-j-1, 0);
					if(type == 2){
						board[numRows-i-1][numCols-j-1] = -1;
					}
				}

				j++;
				k++;
			}
			else {
				j++;
				k++;
			}
		}
		j = 0;
		int prev = -1;
		while(j<numCols) {
			if(board[numRows-i-1][numCols-j-1]==0 && prev == -1) {
				prev = j;
			}
			else if(prev!= -1 && board[numRows-i-1][numCols-1-j]!=0) 
			{
				board[numRows-i-1][numCols-1-prev] = board[numRows-1-i][numCols-1-j];
				board[numRows-i-1][numCols-j-1] = 0;
                addName(make_pair(numRows-i-1, numCols-prev-1), make_pair(numRows-i-1, numRows-j-1));
				j = prev;
				prev = -1;
			}
		
			j++;
		}
			
	}
	changeNegativeToZero();
	return checkIfEqual(board,tempBoard, numRows, numCols);
		//will return true if moves was successful.
}
	

bool moveLeft(int numRows, int numCols, int op) {
	vector<vector<int>> tempBoard{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	copy(tempBoard, board, numRows, numCols);
	
	
	for(int i = 0; i<numRows; i++) {
		//Left. 
		int j = 0;
		int  k = j+1;
		while(j<numCols-1 && k<numCols ) {
			if(board[i][j] == 0) {
				
				j++;
				if(j >= k)
					k++;
			}
			else if(board[i][k]==0) {
				k++;
			}
			else if(board[i][j] == board[i][k]) {
				 if(op == 0)
				    board[i][j]= board[i][j]*board[i][j];
                if(op == 1)
                    board[i][j] = 1;
                if(op == 2){
                   if(type == 1)
                    	board[i][j] = 0;
					if(type == 2)
						board[i][j] = -1;
				   }
                if(op == 3)
                    board[i][j]*= 2;
				board[i][k] = 0;
                addName(make_pair(i, j), make_pair(i, k));
				if(op == 2){
					addTileValue(i, j, 0);
					if(type == 2){
						board[i][j] = -1;
					}
				}
				j++;
				k++;
			}
			else {
				j++;
				k++;
			}
		}
		j = 0;
		int prev = -1;
		while(j<numCols) {
			if(board[i][j]==0 && prev == -1) {
				prev = j;
			}
			else if(prev!= -1 && board[i][j]!=0) 
			{
				board[i][prev] = board[i][j];
				board[i][j] = 0;
                addName(make_pair(i, prev), make_pair(i, j));
				j = prev;
				prev = -1;
			}
		
			j++;
		}
		
	}
	changeNegativeToZero();
	return checkIfEqual(board,tempBoard, numRows, numCols); 
}

bool moveDown(int numRows, int numCols, int op) {
	vector<vector<int>> tempBoard(numRows, vector<int>(numCols, 0));
	copy(tempBoard, board, numRows, numCols);
	for(int i = 0; i<numRows; i++) {
		
		int j = 0;
		int  k = j+1;
		while(j<numCols-1 && k<numCols ) {
			if(board[numCols-1-j][i] == 0) {
				
				j++;
				if(j >= k)
					k++;
			}
			else if(board[numCols-1-k][i]==0) {
				k++;
			}
			else if(board[numCols-1-j][i] == board[numCols-1-k][i]) {
				
                if(op == 0)
				    board[numCols-1-j][i]= board[numCols-1-j][i]*board[numCols-1-j][i];
                if(op == 1)
                    board[numCols-1-j][i] = 1;
                if(op == 2){
					if(type == 1)
                    	board[numCols-1-j][i] = 0;
					if(type == 2)
						board[numCols-1-j][i] = -1;
				}
                if(op == 3)
                    board[numCols-1-j][i]*= 2;
				board[numCols-1-k][i] = 0;
                addName(make_pair(numRows-j-1, i), make_pair(numCols-j-1, i));
				if(op == 2){
					addTileValue(numRows-j-1, i, 0);
					if(type == 2){
						board[numRows-j-1][i] = -1;
					}
				}
				j++;
				k++;
			}
			else {
				j++;
				k++;
			}
		}
		j = 0;
		int prev = -1;
		while(j<numCols) {
			if(board[numCols-1-j][i]==0 && prev == -1) {
				prev = j;
			}
			else if(prev!= -1 && board[numCols-1-j][i]!=0) 
			{
				board[numCols-1-prev][i] = board[numCols-1-j][i];
				board[numCols-1-j][i] = 0;
                addName(make_pair(numRows-prev-1, i), make_pair(numCols-j-1, i));
				j = prev;
				prev = -1;
			}
		
			j++;
		}
		
	}
	changeNegativeToZero();
	return checkIfEqual(board,tempBoard, numRows, numCols);
}

bool moveUp(int numRows, int numCols, int op) {
	vector<vector<int>> tempBoard(numRows, vector<int>(numCols, 0));
	copy(tempBoard, board, numRows, numCols);
	
	for(int i = 0; i<numRows; i++) {
		//Left. 
		int j = 0;
		int  k = j+1;
		while(j<numCols-1 && k<numCols ) {
			if(board[j][i] == 0) {
				
				j++;
				if(j >= k)
					k++;
			}
			else if(board[k][i]==0) {
				k++;
			}
			else if(board[j][i] == board[k][i]) {
                if(op == 0)
				    board[j][i]= board[j][i]*board[j][i];
                if(op == 1)
                    board[j][i] = 1;
                if(op == 2){
					if(type == 1)
                    	board[j][i] = 0;
					if(type == 2)
						board[j][i] = -1;
				}
                if(op == 3)
                    board[j][i]*= 2;
				board[k][i] = 0;
                addName(make_pair(j, i), make_pair(k, i));
				if(op == 2){
					addTileValue(j, i, 0);
					if(type == 2){
						board[j][i] = -1;
					}
				}
				j++;
				k++;
			}
			else {
				j++;
				k++;
			}
		}
		j = 0;
		int prev = -1;
		while(j<numCols) {
			if(board[j][i]==0 && prev == -1) {
				prev = j;
			}
			else if(prev!= -1 && board[j][i]!=0) 
			{
				board[prev][i] = board[j][i];
				board[j][i] = 0;
                addName(make_pair(prev, i), make_pair(j, i));
				j = prev;
				prev = -1;
			}
		
			j++;
		}
		changeNegativeToZero();
		
	}
	return checkIfEqual(board,tempBoard, numRows, numCols);
}


void move(int moveDirection, int op) {
		//Move direction is 0 for left, 1 for right, 2 for up, 3 for down.
        //Op is 0 for multiply, 1 for divide, 2 for subtract, 3 for add. 
		
		if(moveDirection == 0) {
			if(!moveLeft(4,4, op)) {
			cout<<"2048>Left move done, random tile added.\n";
			addRandomTile(1);
			}
		}
		else if(moveDirection == 1) {
			if(!moveRight(4,4, op)){
			cout<<"2048>Right move done, random tile added.\n";
			addRandomTile(1);
			}	
		}
		else if(moveDirection == 2) {
			if(!moveUp(4,4, op)){
			cout<<"2048>Up move done, random tile added.\n";
			addRandomTile(1);
			}
		}
		else if(moveDirection == 3) {
			if(!moveDown(4,4, op)){
			cout<<"2048>Down move done, random tile added.\n";
			addRandomTile(1);
			}
		}
        
		
		
		
		
}
	
int main(int argc, char* argv[]){
	
	if(argc != 2) {
		printf("Please enter the correct number of arguments, it should be executable followed an integer for selecting type. \n");
		return 0;
	}
	type  = atoi(argv[1]);
    srand(time(0));
    cout<<"2048>Hi, I am the 2048-game Engine.\n";
    cout<<"2048>The start state is: \n";
    for(int i = 0; i<4; i++){
        vector<int> row_temp;
        for(int j = 0; j<4; j++){
            row_temp.push_back(0);
        }
        board.push_back(row_temp);
    }
   
    startNewGame();
	cout<<"\n--->";
    yyparse();
    return 0;
}
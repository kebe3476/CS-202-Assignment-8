/*
CS 202 Assignment 8

Name: Keith Beauvais, 5005338658, CS 202 Assignment 8
*/
#include <iostream>
#include <set>
using namespace std;

class archipelago
{
private:
	char ** islands;
	int rows;
	int columns;
	char type;

	//int navR[5]={0,0,0,1,-1}; // did not use since I incremented row and columns manually
	//int navC[5]={0,1,-1,0,0}; // did not use since I incremented row and columns manually

	int navigate(char** &,int, int); 
	bool isSafe(int,int) const;

public:
	archipelago(char[],int,int,char);
	void showIslands(int,int) const;
	int islandsCount(char **);

	char ** getGrid() const;

	void changeColor(char,int,int);

	//bool sameIsland(archipelago&,archipelago&);

};

/*Constructor*/
/* archipelago - constructor that sets that initializes the private variables and the values for the 2D array
	*/
archipelago::archipelago(char colors[],int r,int c,char t)
{
	int index= 0;

    islands = new char *[r];
    for (int i = 0; i < r; i++)
        islands[i] = new char [c];

	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			islands[i][j]= colors[index++];

		}
	}

	rows = r;
	columns = c;
	type = t;

}

/*Function to print the content of an archipelago*/
/*This function was given upon downloading it and given from the TA's on Discord */

void archipelago::showIslands(int r,int c) const
{
	//cout <<"The island is:"<<endl;

	if(r>rows)
		return;

	if(c>columns)
		return;

	if(r<rows)
	{
		if(c<columns)
		{
			cout <<islands[r][c]<<" ";
			showIslands(r,++c);
			return;
		}
		cout <<endl;
		showIslands(++r,0);
	}
	
}

/*Function to make a deep copy of the archipelago grid*/
char** archipelago:: getGrid() const
{
	
	char ** grid=new char *[rows];

	for(int row=0;row<rows;row++)
		grid[row]=new char[columns];

	for(int row=0;row<rows;row++)
	{
		for(int col=0;col<columns;col++)
		{
			grid[row][col]=islands[row][col];
		}
	}

	return grid;

}

/*Function to count the total number of islands in an
archipelago*/
int archipelago::islandsCount(char ** grid)
{
	int totalIslands=0;
	for(int row=0;row<rows;row++)
	{
		for(int col=0;col<columns;col++)
		{
			if(grid[row][col]==type)
				totalIslands+=navigate(grid,row,col);

		}
	}

	return totalIslands;
}
/*Function to navigate the island starting from a position
row and col*/
/* navigate - navigates through the 2D array and changes land to water in the copied grid 

	char ** &grid - this is a copy of the 2D array passed in and is updated since it is passed by reference.

	row - the respective row of where the land begins

	col- the respective column of where the land begins

	return value - returns 1 for the general case or returns 0 for the base case.
	*/
int archipelago::navigate(char ** &grid,int row,int col)
{

	if(isSafe(row,col) == false || grid[row][col] == 'x'){
		return 0;
	}

	grid[row][col]= 'x';

	
	navigate(grid,row +1,col); //down
	navigate(grid,row -1,col); //up
	navigate(grid,row,col+1); // right
	navigate(grid,row,col-1); //left
	
	
	return 1;
	
	
}
/*Function to return true if the provided position is within 
the boundary of the archipelago*/
bool archipelago::isSafe(int r,int c) const
{
	if(r>=0 and r<rows and c>=0 and c<columns)
		return true;
	else
		return false;
}

 /*Function to change the color of an island*/
 /* changeColor - changes the island color from a given starting point and goes through the 2D array throughout that island.

	newColor - the new char color

	r - the respective row of where the land begins

	c- the respective column of where the land begins

	return value - does not return a value.
	*/
void archipelago::changeColor(char newColor,int r,int c)
{
	//base case for checking to make sure not out of bounds or water
	if(isSafe(r,c)==false || islands[r][c] =='x'){
		return;
	}

	//base case checking for already visitied
	if(islands[r][c]==newColor){
		return;
	}

	//changes island to new color
	islands[r][c] = newColor;

	
	changeColor(newColor,r+1,c); //down
	changeColor(newColor,r,c+1); //right
	changeColor(newColor,r-1,c); // up
	changeColor(newColor,r,c-1); // left


}




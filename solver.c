#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "path.h"

char * solveMaze(Maze * m) {//the input here is a pointer to the structure maze..so we have m points to structure Maze
	char * retval = malloc(sizeof(char) * ((m->width * m->height) + 1));//here we are creating space in the heap for the maze which gets the width of the maze m 

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	if (!depthFirstSolve(m, mp, retval, 0)) {
		fprintf(stderr, "No solution found!\n");//this line says that if you dont bave data as it relates to the maze m, you cant find a solution to the maze
	} else {
		printf("Solution found: %s\n", retval);
	}

	return retval;
}

bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step) {

	//FILL IN
	int row = m -> height - curpos.ypos;
	int col = curpos.xpos - 1;
	
	if(curpos.xpos <= 0 || curpos.ypos <= 0)//so not in the maze
	{
	return false;
	}

	else if((curpos.xpos > m -> width) || (curpos.ypos > m -> height))
	{
	return false; 	
	}

	//else if(m -> maze[row][col].type == END){
	//path[step] = '\0';
	//return true;
	//}

	else if(m -> maze[row][col].visited == true)//here we have the key m that points to the maze reach for the x and y values of the maze structure...visited is already an established attribute within a structure Mazesquare that is a boolean value so gets tells us whether the point has been visited 
	{
	return false;
	}
//
	
	else if(m -> maze[row][col].type == WALL){
	return false;
	}

	else if(m -> maze[row][col].type == END){
	path[step] = '\0';
	return true;
	}

	m -> maze[row][col].visited = true;
	MazePos newPos = curpos;
	bool placeChecker = false;
	
	newPos.ypos--;
	placeChecker = depthFirstSolve(m, (MazePos){curpos.xpos, curpos.ypos-1}, path, step + 1);
	if(placeChecker){
	path[step] = SOUTH;
	m -> maze[row][col].visited = false;
	return true;
	}

	else{ newPos.ypos++;
	}

	newPos.ypos++;
	placeChecker = depthFirstSolve(m, (MazePos){curpos.xpos, curpos.ypos+1}, path, step + 1);
	if(placeChecker){
	path[step] = NORTH;
	m -> maze[row][col].visited = false;
	return true;
	}

	else{ newPos.ypos--;
	}

	newPos.xpos++;
	placeChecker = depthFirstSolve(m, (MazePos){curpos.xpos+1, curpos.ypos}, path, step + 1);
	if(placeChecker){
	path[step] = EAST;
	m -> maze[row][col].visited = false;
	return true;
	}

	else{ newPos.xpos--;
	}

	newPos.xpos--;
	placeChecker = depthFirstSolve(m, (MazePos){curpos.xpos-1, curpos.ypos}, path, step + 1);
	if(placeChecker){
	m -> maze[row][col].visited = false;
	path[step] = WEST;
	return true;
	}

	m -> maze[row][col].visited = false;
	return false;
}

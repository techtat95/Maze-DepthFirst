#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

#ifndef READMAZE_OFF
Maze * readMaze(char * mazeFilename) {

	//FILL IN
	Maze* maze1;
	char spotter;
	int check = 0;
	maze1 = malloc(sizeof(*maze1));//allocated space for maze type variable (maze1)
	FILE* fp = fopen(mazeFilename,"r");
	if(fp == NULL)
	{
		return NULL;
	} 
	check = fscanf(fp,"%d %d \n", &(maze1 -> height), &(maze1 -> width));
	if(check != 2){
		//remember to free & fclose
		return NULL;
	}
	
	
	//have to also malloc for rows and columns now that you have done it for larger maze file. You would do it for rows but then you would have to iterate through the number of columns...
	maze1 -> maze = malloc((maze1 -> height) * sizeof(MazeSquare*));//allocating space in heap for array of pointers that help access the columns of arrays ...mazesquare actually makes the arrays of rows while the maze1 -> gives it the set length that it should be
	for(int i = 0; i < (maze1 -> height); i++){
	maze1 -> maze[i] = malloc((maze1 -> width) * sizeof(MazeSquare)); 
	}//for-loop files through the columns that row pointers that are pointing to from beginning to end.
	

	for(int rows = 0; rows < maze1 -> height; rows++){//height is an attribute of a structure so you cannot do rows < height..would have 
		for(int cols = 0; cols < maze1 -> width; cols++){ 
			//if(!feof(fp)){//if not the end of file--** do this action **
			
			if(cols == (maze1 -> width - 1))
			{
				fscanf(fp, "%c\n", &spotter);
			}
			else
			{
				fscanf(fp, "%c", &spotter);
			}

					if(spotter == WALL){
						maze1 -> maze[rows][cols].type = WALL;
						maze1 -> maze[rows][cols].visited = false;
						}//we do maze1 -> maze and not maze1 -> mazesquare because maze is of type mazesquare and we enter types into the malloc functions while maze is what actually gets us the rows and columns 
					else if(spotter == SPACE){
						maze1 -> maze[rows][cols].type = SPACE;
						maze1 -> maze[rows][cols].visited = false;
						}
					else if(spotter == START){
						maze1 -> maze[rows][cols].type = START;
						maze1 -> start.xpos = cols + 1;
						maze1 -> start.ypos = maze1 -> height - rows;
						maze1 -> maze[rows][cols].visited = false;
						}
					else if(spotter == END){
						maze1 -> maze[rows][cols].type = END;
						maze1 -> end.xpos = cols + 1;
						maze1 -> end.ypos = maze1 -> height - rows;
						maze1 -> maze[rows][cols].visited = false;
						}
				
		}
	}
 	//for(int i = 0; i < Height; i++){
	//maze2[i] = malloc(Width*sizeof(*maze[i]))
	//}
	fclose(fp);
	return maze1;
	
}
#endif //#ifndef READMAZE_OFF

#ifndef FREEMAZE_OFF
void freeMaze(Maze * m) {
	//1. Free each of the "rows" of the maze
	for(int i = 0; i< m -> height; i++){
		free(m -> maze[i]);
	}
	//2. Free the "spine" of the array
	free(m -> maze);
}
#endif //#ifndef FREEMAZE_OFF

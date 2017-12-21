#include <stdio.h>
#include <stdlib.h>
#include "path.h"

#ifndef READPATH_OFF
char * readPath(char * pathFilename) {

	long data;
	FILE *fp1; 
	fp1 = fopen(pathFilename,"r");
	if(fp1 == NULL){//so, if file that we open is empty or NULL we return NULL
	return NULL;
	}
	//FILL IN array of characters..first have to check length
	//going to open file and read pathFilename into an array of char
	fseek(fp1, 0, SEEK_END);
	data = ftell(fp1);
	fseek(fp1, 0, SEEK_SET);

	char* reader = malloc(sizeof(char) * data);//always want to have a "type" value in sizeof...could also have *reader because it points to a value of type char (reader* or *reader)

	fscanf(fp1, "%s", reader);
	fclose(fp1);
	
	return reader;

}
#endif //#ifndef READPATH_OFF

#ifndef CHECKPATH_OFF
bool checkPath(Maze * m, char * path) {

	//FILL IN
	char mover;

	int c = m -> start.xpos - 1;
	int r = m -> height - m -> start.ypos;
	int j = 0;
	int placer = 1;

	while(placer == 1){
	placer = 0;
	mover = path[j];
	switch(mover){
	
	case NORTH:
	--r;
	placer = 1;
	break;

	case SOUTH:
	++r;
	placer = 1;
	break;

	case EAST:
	++c;
	placer = 1;
	break;

	case WEST:
	--c;
	placer = 1;
	break;
	
	
}
	if(placer == 1){
		if ((r<0) || (c<0))
		{
			return false;
		}
		else if ((c >=  m -> width) || (r >= m -> height)){
			return false;
		}
		else if (m -> maze[r][c].type == END){
			return true;
		}
		else if (m -> maze[r][c].visited == true){
			return false;
		}
		else if (m -> maze[r][c].type == WALL){
			return false;
		}

		m -> maze[r][c].visited = true;
		
		++j;
	}
	
}



	if(m -> maze[r][c].type == END){
		return true;
	}
	else{
		return false;
	}
}

#endif //#ifndef CHECKPATH_OFF

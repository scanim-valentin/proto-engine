//Prints
#include <stdio.h>
/* librairie standard ... */
#include <stdlib.h>
//Managing strings
#include <string.h>

/*
 * Generates an image sequence based on intial conditions provided in a text file
*/

typedef struct square{
	
	int x; //Coordinates of the upper left corne 
	int y;
	int size; //Size of the sides
	
}	Square;

typedef struct circle{
	
	int x; //Coordinates of the center 
	int y;
	int radius; //Radius
	
}	Circle;



int main(int argc, char * argv[]){
	//Initiating sequence lenght 
	int nbIter = atoi(argv[1]);
	//Retrieving the initial conditions
	char sceneFile[50];
	printf("%d\n",0);
	strcpy(sceneFile,argv[2]); 
	printf("%d\n",0);
	printf("%s\n",sceneFile);
	
	/*
	for(int i = 0 ; i<nbIter ; i++){
	
	    //Updating parameters
	
	    //Generating new frame
	
	}
	*/

}

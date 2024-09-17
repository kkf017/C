#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../Global.h"
#include "../Tools/Tools.h"

void changedir(char **argv, int argc){
    if(argc > 2){
        //exitf("\n[-]ERROR: Unknown command.");
        printf("\n\033[1;91m[-]ERROR: Unknown command.\033[0m");
    }else{

        if(argc == 1){
            chdir(HOME);
        }else{

            char *path = realpath(*(argv+1), NULL);
            if(path == NULL){
                printf("\n\033[1;91m[-]WARNING: Unknown PATH.\033[0m");

            }else{
                chdir(path);
                free(path);
            } 
        } 
    }
}


char **shprogram(char **argv, int argc, char *bin, char *path){
    // function to read and run script.sh
    
    char **argvCorn = malloc((argc+2) * sizeof(char *));
	int i;

    *(argvCorn) = malloc(sizeof(char) * (strlen(bin)+1));
	strcpy(*(argvCorn), bin);

    //*(argvCorn+1) = malloc(sizeof(char) * (strlen(path)+1));
	//strcpy(*(argvCorn+1), path);

	for(i = 1; i < argc; i++){
	    *(argvCorn+i) = malloc(sizeof(char) * (strlen(*(argv+i))+1));
	    strcpy(*(argvCorn+i), *(argv+i));
	}
	*(argvCorn+(i+1)) = NULL;

	return argvCorn;
}


void cprogram(char **argv, int argc){
    // function to read and run prog.c
    // execv(*argv, argv)
}


void pyprogram(char **argv, int argc){
    // function to read and run prog.py
    // execv(*argv, argv)
}

void perlprogram(char **argv, int argc){
    // function to read and run prog.pl
    // execv(*argv, argv)
}


char **unixcorn(char **argv, int argc, char *bin, char *path){
    //char *bin = "/usr/bin/python3";
    //char *path = "/home/user/Documents/hello/main.py";

    char **argvCorn = malloc((argc+2) * sizeof(char *));
	int i;

    *(argvCorn) = malloc(sizeof(char) * (strlen(bin)+1));
	strcpy(*(argvCorn), bin);

    *(argvCorn+1) = malloc(sizeof(char) * (strlen(path)+1));
	strcpy(*(argvCorn+1), path);

	for(i = 1; i < argc; i++){
	    *(argvCorn+(i+1)) = malloc(sizeof(char) * (strlen(*(argv+i))+1));
	    strcpy(*(argvCorn+(i+1)), *(argv+i));
	}
	*(argvCorn+(i+1)) = NULL;

	return argvCorn;
}

void freeUnixcorn(char **arr, int n){
	for (int i = 0; i < n+1; i++){
	    free(*(arr+i)); 
	    *(arr+i) = NULL;
	}
	free(arr);
	arr = NULL;
}

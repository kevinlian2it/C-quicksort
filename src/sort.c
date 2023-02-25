#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024 

void display_usage() {
    printf("Usage: ./sort [-i|-d] [filename]\n");
    printf("  -i: Specifies the input contains ints.\n");
    printf("  -d: Specifies the input contains doubles.\n");
    printf("  filename: The file to sort. If no file is supplied, input is read from stdin.\n");
    printf("  No flags defaults to sorting strings.\n");
}

int main(int argc, char* argv[]) {
    	int opt;
    	int flag_int = 0;
    	int flag_db = 0;
    	char* filename = NULL;
    	while ((opt = getopt(argc, argv, "id")) != -1) {
        	switch (opt) {
        	    	case 'i':
                		flag_int = 1;
                		break;
            		case 'd':
                		flag_db = 1;
                		break;
            		case '?':
                		fprintf(stderr, "Error: Unknown option '-%c'.\n", optopt);
                		display_usage();
                		EXIT_FAILURE;
            		default:
                		display_usage();
                		EXIT_FAILURE;
        	}
    	}
   	if (optind < argc) {
        	filename = argv[optind];
    	}
    	// Rest of the code goes here.
    	return EXIT_SUCCESS;
}

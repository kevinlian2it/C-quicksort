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
    	printf("   -i: Specifies the input contains ints.\n");
    	printf("   -d: Specifies the input contains doubles.\n");
    	printf("   filename: The file to sort. If no file is supplied, input is read from\n             stdin.\n");
    	printf("   No flags defaults to sorting strings.\n");
}

int main(int argc, char** argv) {
        int opt;
        int flag_int = 0;
        int flag_db = 0;
        char* filename = NULL;
        while ((opt = getopt(argc, argv, ":id")) != -1) {
                switch (opt) {
                        case 'i':
                                flag_int = 1;
                                break;
                        case 'd':
                                flag_db = 1;
                                break;
                        case '?':
                                fprintf(stderr, "Error: Unknown option '-%c' received.\n", optopt);
                                display_usage();
                                return EXIT_FAILURE;
                        default:
                                display_usage();
                                return EXIT_FAILURE;
                }        }
        if ((argc - optind) > 1) {
                fprintf(stderr, "Error: Too many files specified.\n");
                return EXIT_FAILURE;
        }
        if (optind == argc-1) {
                filename = argv[optind];
        }
	
	FILE* input = stdin;
	if (filename) {
    		input = fopen(filename, "r");
    		if (input == NULL) {
        		fprintf(stderr, "Error: Cannot open '%s'. No such file or directory.\n", filename);
        		return EXIT_FAILURE;
    		}
	}
	void **input_arr = malloc(MAX_ELEMENTS * sizeof(void *));
	int num_elements = 0;
	char *buf = malloc(MAX_STRLEN);
	char *line;
	
	if (!input) {
	    fprintf(stderr, "Failed to open input file\n");
	    exit(1);
	}

	while (num_elements < MAX_ELEMENTS && fgets(buf, MAX_STRLEN, input)) {
	    line = strchr(buf, '\n');
	    if (line) {
	        *line = '\0';
    		} 
	    else {
	        buf[MAX_STRLEN - 1] = '\0';
	    }
	    int c;
	    while ((c = fgetc(input)) != '\n' && c != EOF);
	    input_arr[num_elements] = strdup(buf);
	    num_elements++;
	}
		
	printf("Input array:\n");
	for (int i = 0; i < num_elements; i++) {
	    printf("%s\n", (char *)input_arr[i]);
	}
  	
	printf("Weird input array:%s\n",(char *)input_arr);	
       
	if (flag_int) {
    		quicksort((int **)input_arr, num_elements, sizeof(int *), int_cmp);
	} else if (flag_db) {
    		quicksort((double **)input_arr, num_elements, sizeof(double *), dbl_cmp);
	} else {
    		quicksort((char **)input_arr, num_elements, sizeof(char *), str_cmp);
	}
	
	printf("Array after sorted:\n");
        for (int i = 0; i < num_elements; i++) {
            printf("%s\n", (char *)input_arr[i]);
        }

	free(input_arr);
	free(buf);

        if(filename) {
        	fclose(input);
        }
        return EXIT_SUCCESS;
}

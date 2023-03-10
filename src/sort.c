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
	if(flag_int + flag_db == 2) {
		fprintf(stderr, "Error: Too many flags specified.\n");
		return EXIT_FAILURE;
	}
        if ((argc - optind) > 1) {
                fprintf(stderr, "Error: Too many files specified.\n");
                return EXIT_FAILURE;
        }
        if (optind == argc-1) {
                filename = argv[optind];
        }
	
// Open the file for reading
    FILE *fp;
    if (filename) {
        fp = fopen(filename, "r");
        if (!fp) {
            fprintf(stderr, "Error: Cannot open file '%s'. No such file or directory.\n", filename);
            return EXIT_FAILURE;
        }
    } else {
        fp = stdin;
    }

        // Read the data into an array
    char** data = (char**) malloc(MAX_ELEMENTS * sizeof(char*));
    int i;
    for (i = 0; i < MAX_ELEMENTS; i++) {
        char* str = (char*) malloc(MAX_STRLEN * sizeof(char));
        if (!fgets(str, MAX_STRLEN, fp)) {
            free(str);
            break;
        }
        str[strcspn(str, "\n")] = 0; // Remove newline character
        data[i] = str;
    }
    int num_elements = i;

    // Sort the data
	if (flag_int) {
    int* int_data = (int*) malloc(num_elements * sizeof(int));
    for (i = 0; i < num_elements; i++) {
        int_data[i] = atoi(data[i]);
    }
    quicksort(int_data, num_elements, sizeof(int),int_cmp);
    for (i = 0; i < num_elements; i++) {
        printf("%d\n", int_data[i]);
    }
    free(int_data);
} else if (flag_db) {
    double* db_data = (double*) malloc(num_elements * sizeof(double));
    for (i = 0; i < num_elements; i++) {
        db_data[i] = atof(data[i]);
    }
    quicksort(db_data,num_elements,sizeof(double),dbl_cmp);
    for (i = 0; i < num_elements; i++) {
        printf("%f\n", db_data[i]);
    }
    free(db_data);
} else {
    quicksort(data,num_elements,sizeof(char *),str_cmp);
    for (i = 0; i < num_elements; i++) {
        printf("%s\n", data[i]);
    }
}
    for (i = 0; i < num_elements; i++) {
    	free(data[i]);
    }
    free(data);

    // Close the file
    if (filename) {
        fclose(fp);
    }

    return EXIT_SUCCESS;
}


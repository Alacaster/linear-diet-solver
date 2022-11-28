#include <stdio.h>
#include <stddef.h>
#include <lapacke.h>
#include <string.h>
#include <sys/stat.h>

void __attribute__((always_inline)) skipline(char * buffer, int * buf_loc, int maxbuf){
    while(*buf_loc < maxbuf && buffer[*buf_loc] != '\n'){
        *buf_loc++;
    }
    *buf_loc++;
}

#define buf buffer[buf_loc]
#define skipifcomment if(buf == '#') do{skipline(buffer, &buf_loc, &buffer_size); if(buf_loc >= buffer_size) return status;}while(0)
typedef enum {SUCCESS, BAD_FORMAT, BAD_POINTER} lde_t;
lde_t loaddata(int col, int row, double * array, char *** prownames, char ** rownamedata, char *** pcolnames, char ** colnamedata){
    lde_t status = BAD_FORMAT; //once we finish the nutrients i.e. find an empty line, then we set this to SUCCESS because finding EOF doesn't mean we are missing data anymore
    if(array = NULL){return BAD_POINTER;}
    char * buffer = NULL;
    int buffer_size;
    FILE* file = fopen("data.txt", "r");
    if(file == NULL){perror("fopen() failed");}
    {struct stat hello; fstat(fileno(file), &hello); buffer_size = hello.st_size;}
    buffer = malloc(buffer_size);
    if(buffer = NULL){perror("error opening monolithic file, probably too large");}
    fread(buffer, 1, buffer_size, file);
    int buf_loc = 0; //now let's make some stack space to store the strings for the data
    char *prownames_stack[col], *rownamedata_stack, *pcolnames_stack[row], *colnamedata_stack;
    rownamedata_stack = malloc(1024*sizeof(*rownamedata_stack));
    while(buf_loc < buffer_size){
        skipifcomment
    }
}
#undef skipifcomment
#undef buf

int main(){
    printf("hello world!");
    double * nutrient_data = (double*)malloc(sizeof(double)*47*16);
    char ** pnutrient_names, pingredient_names; //array of pointer to char, the beginning of null terminated strings
    char * nutrient_names, ingredient_names; //null terminated strings array
    loaddata(47, 16, nutrient_data, pnutrient_names, nutrient_names, pingredient_names, ingredient_names);
    return 0;
}

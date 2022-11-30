#include <stdio.h>
#include <stddef.h>
#include <lapacke.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>

#define buf buffer[buf_loc]
typedef enum {SUCCESS, BAD_FORMAT, BAD_POINTER, DATA_MISSING, TOO_MUCH_DATA} lde_t;
lde_t loaddata(int * const ccol, int * const crow, double ** const array, 
char *** const prownames, char ** const rownamedata, char *** const pcolnames, char ** const colnamedata){
    *ccol = *crow = 0;
    char * buffer;
    int buffer_size;
    FILE* file = fopen("data.txt", "rb");
    if(file == NULL){perror("fopen() failed");}
    {struct stat hello; fstat(fileno(file), &hello); buffer_size = hello.st_size;}
    buffer = malloc(buffer_size);
    if(buffer = NULL){perror("error opening monolithic file, probably too large");}
    fread(buffer, 1, buffer_size, file);
    int buf_loc = 0;
    int datalength = 0, datasize = 1024;
    *rownamedata = malloc(datasize*sizeof(**rownamedata));
    bool seennewline = false;
    while(++buf_loc < buffer_size && isspace(buf));
    while(1){ //we are on the first character that is not isspace
        if(buf_loc >= buffer_size) return DATA_MISSING;
        else if(buf = '#'){while(1){ //upon '#' find and stay on the next newline 
                if(++buf_loc >= buffer_size) return DATA_MISSING;
                else if(buffer[buf_loc] == '\n') break;}}
        else if(buf == '\r'){buf_loc++; continue;}
        else if(buf == '\n'){buf_loc++; if(seennewline == true) break; else{
            seennewline = true;
            (*rownamedata)[datalength++] = '\0';
            (*crow)++;
            }}
        else if(isalnum(buf) || buf == ' '){seennewline = false;
            if(datalength >= datasize){
                if(!realloc(*rownamedata, datasize+=1024)) return TOO_MUCH_DATA;}
            (*rownamedata)[datalength++] = buffer[buf_loc++];}
        else return BAD_FORMAT;
    } //exiting this loop we are pointing at the first character after two consecutive newlines
    int setback = 0; //let's remove excess white space
    int row = 0;     //and note the string pointers in *prownames
    bool seenspace = true;
    (*prownames)[0]=*rownamedata;
    for(int i = 0; i <= datalength; i++){ char a;
        if((a=(*rownamedata)[i-setback]=(*rownamedata)[i]) == ' ' && seenspace) setback++;
        else if(a == '\0'){
            (*prownames)[row++] = &(*rownamedata)[i-setback+1];
            if((*rownamedata)[i-1] == ' ') setback++;
        }
        else seenspace = false;
    }//and then shrink the array;
    datalength -= setback; realloc(*rownamedata, sizeof(**rownamedata)*datalength);
    //next section ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    datalength = 0; datasize = 1024;
    *colnamedata = malloc(datasize*sizeof(**colnamedata));
    seennewline = false;
    while(++buf_loc < buffer_size && isspace(buf));
    //we are on the first nonspace character
    unsigned int data_acquired = 0;//inremented when we add a number to *array should be m*n when we finish
    int length_of_number, column_numbers_counted;
    row = 0;
    int b; //temporarily holds value of a test for using it twice
    while(1){
        double a[*ccol][*crow]; //crow is constant here
        seennewline = true;
        while(1){
            if(buf_loc >= buffer_size) return DATA_MISSING;
            else if(isalnum(buf) || buf == ' '){
                if(datalength >= datasize){
                    if(!realloc(*colnamedata, datasize+=1024)) return TOO_MUCH_DATA;}
                (*colnamedata)[datalength++] = buffer[buf_loc++]; seennewline = false;}
            else if(buf == '\n') return DATA_MISSING;
            else if(buf == ',' && seennewline == 0){(*colnamedata)[datalength++] = '\0'; break;}
            else return BAD_FORMAT;
        }//we started on the first non-space character on a new line, if we encountered only alnums, we
        //exited the loop upon finding ',' and wrote a '\0' we are on that comma still
        column_numbers_counted = 0;
        while(1){
            length_of_number = 1;
            if(buf_loc >= buffer_size) return DATA_MISSING;
            if(buf == ' ' || buf == ','){buf_loc++; continue;}
            else if(isdigit(buf) || buf == '.'){
                if(++column_numbers_counted >= (*crow)) return BAD_FORMAT;
                while(1){
                    if(++buf_loc >= buffer_size) return DATA_MISSING;
                    if(isdigit(buf) || buf == '.') length_of_number++;
                    else if(buf == ' ' || buf == ',' || (b=(buf == '\n' | buf == '\r'))){
                        buf = '\0'; break;}
                    else return BAD_FORMAT;
                }
                a[row][column_numbers_counted] = atof(buffer + buf_loc - length_of_number);
                if(b){
                    if(column_numbers_counted+1 != (*crow)) return DATA_MISSING;
                    else break;
                }
            }
            else if(buf == '\r'){buf_loc++; continue;}
        }
        (*ccol)++;
    }
    if((*ccol)*(*crow) != data_acquired) return DATA_MISSING;
    setback = 0; seenspace = true;
    for(int i = 0; i <= datalength; i++){ char a;
        if((a=(*colnamedata)[i-setback]=(*colnamedata)[i]) == ' ' && seenspace) setback++;
        else if(a == '\0') (*pcolnames)[row++] = &(*colnamedata)[i-setback+1];
        else seenspace = false;
    }
    return SUCCESS;
}
#undef buf

int main(){
    double * nutrient_data;
    int m, n;
    char ** pnutrient_names, pingredient_names; //array of pointer to char, the beginning of null terminated strings
    char * nutrient_names, ingredient_names; //null terminated strings array
    loaddata(&m, &n, &nutrient_data, &pnutrient_names, &nutrient_names, &pingredient_names, &ingredient_names);

    return 0;
}
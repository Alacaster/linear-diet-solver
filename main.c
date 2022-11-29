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
    while(1){
        if(buf_loc >= buffer_size) return DATA_MISSING;
        else if(buf = '#'){while(1){
                if(buf_loc >= buffer_size) return DATA_MISSING;
                else if(buffer[buf_loc] == '\n') break;
                buf_loc++;}}
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
    }
    int setback = 0; //let's remove excess white space
    int row = 0;
    bool seenspace = true;
    (*prownames)[0]=*rownamedata;
    for(int i = 0; i <= datalength; i++){ char a;
        if((a=(*rownamedata)[i-setback]=(*rownamedata)[i]) == ' ' && seenspace) setback++;
        else if(a == '\0') (*prownames)[row++] = &(*rownamedata)[i-setback+1];
        else seenspace = false;
    } //and then shrink the array;
    datalength -= setback; realloc(*rownamedata, sizeof(**rownamedata)*datalength);
    //next section!
    datalength = 0; datasize = 1024;
    *colnamedata = malloc(datasize*sizeof(**colnamedata));
    seennewline = false;
    while(++buf_loc < buffer_size && isspace(buf));
    //load the ingredient names and nutrient data
    unsigned int data_acquired = 0;
    unsigned int characters = 0;
    int length_of_number, column_numbers_counted;
    while(1){
        double a[*ccol][*crow]; //crow is constant here
        characters = 0;
        while(1){
            if(buf_loc >= buffer_size) return DATA_MISSING;
            else if(isalnum(buf) || buf == ' '){
                if(datalength >= datasize){
                    if(!realloc(*colnamedata, datasize+=1024)) return TOO_MUCH_DATA;}
                (*colnamedata)[datalength++] = buffer[buf_loc++]; characters++;}
            else if(buf == '\n') return DATA_MISSING;
            else if(buf == ',' && characters != 0){(*colnamedata)[datalength++] = '\0'; break;}
            else return BAD_FORMAT;
        }
        column_numbers_counted = 0;
        while(1){
            length_of_number = 1;
            if(buf == ' ' || buf == ','){buf_loc++; continue;}
            else if(isdigit(buf) || buf == '.'){
                while(1){
                    buf_loc++;
                    if(isdigit(buf) || buf == '.') length_of_number++;
                    else if(buf == ' ' || buf == ',') buf = '\0';
                    else if(buf == '\r') continue;
                    else if(buf == '\n'){
                        if(column_numbers_counted+1 != ())
                    }
                else return BAD_FORMAT;
                //add the number to the array
                column_numbers_counted++;
                }}
            else if(buf == '\r'){buf_loc++; continue;}
        }
        
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
    printf("hello world!");
    double * nutrient_data;
    int m, n;
    char ** pnutrient_names, pingredient_names; //array of pointer to char, the beginning of null terminated strings
    char * nutrient_names, ingredient_names; //null terminated strings array
    loaddata(&m, &n, &nutrient_data, &pnutrient_names, &nutrient_names, &pingredient_names, &ingredient_names);
    return 0;
}

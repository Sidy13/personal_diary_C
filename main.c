//
// Created by Sidy on 03/06/2023.
//
#include <stdio.h>
#include "fonctions.h"

int main() {
    //char* pass = password();
    char data[1000];


    printf("%s", pass);
    FILE*  fptr;
    fptr = fopen("file1.txt","w");

    if(fptr == NULL){
        printf("Unable to create file\n");
        return 1;
    }
    printf("Enter contents to store in file : \n");
    fgets(data,1000,stdin);

    fputs(data,fptr);
    fclose(fptr);

    printf("file created and saved succesfully");

    return 0;

}

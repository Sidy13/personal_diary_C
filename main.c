//
// Created by Sidy on 03/06/2023.
//
#include <stdio.h>
#include "fonctions.h"

int main() {
    //char* pass = password();
    char data[1000];


    FILE*  fptr;
    fptr = fopen("../data/file2.txt","w");
    fputs("popo",fptr);
    fclose(fptr);


    return 0;

}

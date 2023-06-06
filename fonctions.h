//
// Created by Sidy on 04/06/2023.
//

#ifndef C_SHELL_FONCTIONS_H
#define C_SHELL_FONCTIONS_H
#define Date_max 365
#include <stdio.h>


typedef struct {
    int jour;
    int mois;
    int annee;
    char description[100];
} DATE;

typedef struct {
    DATE evenement[Date_max];
    int count;
} AGENDA;

void ajout(AGENDA *);
int len_password();
char* create_password();
void save_password(char* password);
int password_verif(char* password);
void addrecord();

#endif //C_SHELL_FONCTIONS_H
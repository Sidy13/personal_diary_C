//
// Created by Sidy on 04/06/2023.
//

#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ajout(AGENDA* agenda){
    DATE event;
    if (agenda->count >= Date_max){
        printf("L'évenement ne peut pas être ajouté dans l'agenda");
        return;
    }
    else{
        printf("Entrez la date de l'évenement sous la forme jour mois année :");
        scanf("%d %d %d", &event.jour, &event.mois, &event.annee);
        printf("\nDécrivez l'évenement\n");
        getchar();
        fgets(event.description, sizeof(event.description), stdin);
        agenda->evenement[agenda->count++] = event;
        printf("\nL'évenement a été ajouté dans l'agenda\n");
    }
}

int len_password() {
    int length = 0;
    printf("Voulez-vous un mot de passe à 4 chiffres, 6 chiffres ou 12 chiffres ?\n");
    do {
        printf("Ecrivez soit '4' soit '6' soit '12' :\n");
        scanf("%d", &length);
        if (length != 4 && length != 6 && length != 12) {
            printf("Longueur de mot de passe invalide. Veuillez réessayer.\n");
        }
    } while (length != 4 && length != 6 && length != 12);
    return length;
}


char* create_password() {
    char *password = (char *) malloc(sizeof(char)*40);
    int special_count = 0;
    int number_count = 0;
    int uppercase_count = 0;
    int password_len = 0;


    do{
        printf("Entrez votre mot de passe :\n");
        printf("Votre mot de passe doit contenir au moins un caractere special, une lettre majuscule et un chiffre");
        fgets(password, sizeof(password), stdin);
        password_len = strlen(password);
        for (int i = 0;i<password_len;i++) {
            if (password[i] > 47 && password[i] < 58) {
                number_count++;
            } else {
                if (!((password[i] > 64 && password[i] < 91) || (password[i] > 96 && password[i] < 123))) {
                    special_count++;
                } else if (password[i] > 64 && password[i] < 91) {
                    uppercase_count++;
                }
            }
            printf("%c", password[i]);
        }



    }while(special_count==0 ||number_count == 0 || uppercase_count == 0);
    return password;
}

void save_password(char* password){
    FILE*  fptr;
    fptr = fopen("../data/password.txt","w");

    if(fptr == NULL){
        printf("Impossible d'enregistrer le mot de passe\n");
    }
    fputs(password,fptr);
    fclose(fptr);

    printf("Mot de passe enregistré !");
}

void password_verif(){
d
}
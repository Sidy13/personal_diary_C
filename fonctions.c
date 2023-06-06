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
        printf("Entrez votre mot de passe (votre mot de passe doit contenir au moins un caractere special, une lettre majuscule et un chiffre): \n");
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
    save_password((password));
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

    printf("Mot de passe enregistr !");
}

int password_verif(char* password){
    char * verif = create_password();
    if (strcmp(password, verif) != 0){
        printf("Mot de passe éronné");
        return 0;
    }
    else {
        //Créer une fonction qui fait rentrer dans le journal;
    }
}



void addrecord()
{
    //initialise un tableau de char qui va nous servir de texte
    char phrase[1000];

    //ouverture du fichier + ecriture
    FILE* fichier = fopen("record.txt", "a");

    //saisie du texte qu'on veut ajouter
    printf("Veuillez saisir une phrase : ");
    fgets(phrase, sizeof(phrase), stdin);

    //ajout de la date



    //ajout du texte dans le fichier
    fprintf(fichier, "%s", phrase);

    //fermeture du fichier
    fclose(fichier);
}
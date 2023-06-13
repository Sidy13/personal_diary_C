//
// Created by Sidy on 04/06/2023.
//

#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"


//void ajout(AGENDA* agenda){
//    DATE event;
//    if (agenda->count >= Date_max){
//        printf("L'évenement ne peut pas être ajouté dans l'agenda");
//        return;
//    }
//    else{
//        printf("Entrez la date de l'évenement sous la forme jour mois année :");
//        scanf("%d %d %d", &event.jour, &event.mois, &event.annee);
//        printf("\nDécrivez l'évenement\n");
//        getchar();
//        fgets(event.description, sizeof(event.description), stdin);
//        agenda->evenement[agenda->count++] = event;
//        printf("\nL'évenement a été ajouté dans l'agenda\n");
//    }
//}

//int len_password() {
//    int length = 0;
//    printf("Voulez-vous un mot de passe à 4 chiffres, 6 chiffres ou 12 chiffres ?\n");
//    do {
//        printf("Ecrivez soit '4' soit '6' soit '12' :\n");
//        scanf("%d", &length);
//        if (length != 4 && length != 6 && length != 12) {
//            printf("Longueur de mot de passe invalide. Veuillez réessayer.\n");
//        }
//    } while (length != 4 && length != 6 && length != 12);
//    return length;
//}


/*char* create_password() {
    char *password = (char *) malloc(sizeof(char) * 40);
    int special_count = 0;
    int number_count = 0;
    int uppercase_count = 0;
    int password_len = 0;

    do {
        printf("Entrez votre mot de passe (votre mot de passe doit contenir au moins un caractere special, une lettre majuscule et un chiffre): \n");
        fgets(password, 40, stdin);
        password_len = strlen(password);

        for (int i = 0; i < password_len; i++) {
            if (password[i] >= '0' && password[i] <= '9') {
                number_count++;
            } else if ((password[i] >= '!' && password[i] <= '/') || (password[i] >= ':' && password[i] <= '@') || (password[i] >= '[' && password[i] <= '`') || (password[i] >= '{' && password[i] <= '~')) {
                special_count++;
            } else if (password[i] >= 'A' && password[i] <= 'Z') {
                uppercase_count++;
            }
            else if (password[i] >= 'a' && password[i] <= 'z') {
                uppercase_count++;
            }
            printf("%c", password[i]);
        }
    } while (special_count == 0 || number_count == 0 || uppercase_count == 0);

    save_password(password);
    return password;
}*/


int special_character(char c) {
    char special_characters[] = "!@#$%^&*()_+-={}[]|\\:;\"'<>,.?/";

    for (int i = 0; i < strlen(special_characters); i++) {
        if (c == special_characters[i]) {
            return 1;
        }
    }

    return 0;
}

void save_password(char* password) {
    FILE*  fptr;
    fptr = fopen("../data/password.txt", "w");

    if (fptr == NULL) {
        printf("Impossible d'enregistrer le mot de passe\n");
    } else {
        fputs(password, fptr);
        fclose(fptr);
        printf("Mot de passe enregistre !\n");
    }
}


char* create_password() {
    char* password = (char*) malloc(sizeof(char) * 40);
    int uppercase_count = 0;
    int lowercase_count = 0;
    int special_count = 0;
    int digit_count = 0;

    do {
        printf("Entrez votre mot de passe (votre mot de passe doit contenir au moins une majuscule, une minuscule, un caractere special et un chiffre): \n");
        fgets(password, 40, stdin);

        for (int i = 0; password[i] != '\0'; i++) {
            if (password[i] >= 'A' && password[i] <= 'Z')
                uppercase_count++;
            else if (password[i] >= 'a' && password[i] <= 'z')
                lowercase_count++;
            else if (password[i] >= '0' && password[i] <= '9')
                digit_count++;
            else if (special_character(password[i]))
                special_count++;
        }

        if (!(uppercase_count >= 1 && lowercase_count >= 1 && special_count >= 1 && digit_count >= 1)) {
            printf("Le mot de passe ne satisfait pas les conditions. Veuillez réessayer.\n");
            uppercase_count = 0;
            lowercase_count = 0;
            special_count = 0;
            digit_count = 0;
        }
    } while (!(uppercase_count >= 1 && lowercase_count >= 1 && special_count >= 1 && digit_count >= 1));

    save_password(password);
    return password;
}





int password_verif() {
    char verif[100];
    char password[100];

    FILE* fptr = fopen("../data/password.txt", "r");
    if (fptr == NULL) {
        printf("Impossible d'ouvrir le fichier de mot de passe.\n");
        return 0;
    }

    if (fgets(verif, sizeof(verif), fptr) == NULL) {
        printf("Erreur lors de la lecture du mot de passe dans le fichier.\n");
        fclose(fptr);
        return 0;
    }

    fclose(fptr);

    // Supprimer les caractères de nouvelle ligne du mot de passe stocké
    verif[strcspn(verif, "\n")] = '\0';

    printf("Entrez votre mot de passe : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(password, verif) == 0) {
        printf("Mot de passe correct.\n");
        return 0;
    } else {
        printf("Mot de passe incorrect");
        return 1;
    }
}


void enter_diary(int choice){

    switch (choice) {
        case 1:
            addrecord();
            break;
        case 2:
//            printRecord();
            break;
        case 3:
//            editRecord();
            break;
        case 4:
//            deleterecord();
            break;
        case 5:
//            editPassword();
            break;
        case 6:
            exit(0);

    }
}

void viewRecord(){
    FILE *fptr;
    char c;
    fptr = fopen("../data/record.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    while((c=fgetc(fptr)) != EOF){
        putchar(c);
    }
    fclose(fptr);


}


void stop_password(int choice) {
    int count = 0; // Initialisez count à 0

    do {
        if (password_verif() == 0) {
            count++;
        } else {
            enter_diary(choice);
        }

        if (count == 3) {
            return; // Arrêtez la fonction après trois mots de passe erronés
        }

    } while (1); // Utilisez 1 comme condition pour une boucle infinie
}


void addrecord()
{
    //partie où ya la date :

    //le temps écoulé depuis le 1er janvier 1970 (no troll)
    time_t temps;
    //La structure tm contient les informations de date et d'heure
    struct tm* date;

    //le temps actuel en secondes depuis l'époque (1er janvier 1970)
    temps = time(NULL);
    //convertir le temps stocké dans "temps" en une structure "tm" pour avoir je crois la date avec les jours, mois, année
    date = localtime(&temps);

    int jour = date->tm_mday;
    int mois = date->tm_mon + 1;
    int annee = date->tm_year + 1900;

    //partie ou ya l'agenda :

    //initialise un tableau de char qui va nous servir de texte
    char phrase[1000];

    //ouverture du fichier + ecriture
    FILE* fichier = fopen("../data/record.txt", "a");

    //saisie du texte qu'on veut ajouter
    printf("Veuillez saisir une phrase : ");
    fgets(phrase, sizeof(phrase), stdin);

    //ajout de la date dans le fichier
    fprintf(fichier, "Date : %02d/%02d/%04d --> ", jour, mois, annee);

    //ajout du texte dans le fichier
    fprintf(fichier, "%s\n", phrase);

    //fermeture du fichier
    fclose(fichier);
}
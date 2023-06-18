//
// Created by Sidy on 04/06/2023.
//

#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"

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



int special_character(char c) {
    char special_characters[] = "!@#$%^&*()_+-={}[]|\\:;\"'<>,.?/";

    for (int i = 0; i < strlen(special_characters); i++) {
        if (c == special_characters[i]) {
            return 1;
        }
    }

    return 0;
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


void save_password(char* password) {
    FILE*  fptr;
    fptr = fopen("../data/password.txt", "w");

    if (fptr == NULL) {
        printf("Impossible d'enregistrer le mot de passe\n");
    } else {
        fputs(password, fptr);
        fclose(fptr);
        printf("Mot de passe enregistré !\n");
    }
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
        printf("Mot de passe incorrect\n");
        return 1;
    }
}



void stop_password() {
    int count = 0; // Initialisez count à 0
    int choice = 0;

    do {
        if (password_verif() == 1) {
            count++;
        } else {
            break;
        }

        if (count == 3) {
            return; // Arrêtez la fonction après trois mots de passe erronés
        }

    } while (1); // Utilisez 1 comme condition pour une boucle infinie
    enter_diary(choice);
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
    fprintf(fichier, "%02d/%02d/%04d : ", jour, mois, annee);

    //ajout du texte dans le fichier
    fprintf(fichier, "%s\n", phrase);

    //fermeture du fichier
    fclose(fichier);
}


/*void editrecord(){
    int j, m, a;
    int jour, mois, annee;
    char phrase[1000];
    FILE * fic;
    FILE * fp = fopen("../data/record.txt", "rt");
    if ( fp == NULL){
        printf("Ouverture impossible !!!!");
        exit(1);
    }
    fic = fopen("temp.txt", "wt");
    if ( fic == NULL){
        printf("Ouverture impossible !!!!");
        exit(1);
    }
    printf("Quelle date voulez-vous modifier : \n");
    printf("VEUILLEZ SAISIR LA DATE SOUS LA FORME J/M/A \n");
    scanf("%d/%d/%d", &j, &m, &a);




}*/

/*void deleterecord() {
    int jour, mois, annee;
    int j, m, a;
    char phrase[1000];
    FILE * pf;
    FILE * fic;
    pf = fopen("../data/record.txt", "r");
    if (pf == NULL) {
        printf("ERREUR");
        exit(1);
    } else {
        fic = fopen("temp.txt", "w");
    }
    if (fic == NULL) {
        printf("ERREUR");
        exit(1);
    } else {
        printf("Saisir la date sous la forme J/M/A : \n");
        scanf("%d/%d/%d", &j, &m, &a);
        while (fscanf(pf, "%d/%d/%d\n%s", &jour, &mois, &annee, phrase) != EOF) {
            if (!(jour == j && mois == m && annee == a)) {
                fprintf(fic, "%d/%d/%d\n%s\n", jour, mois, annee, phrase);
            }
        }
        fclose(pf);
        fclose(fic);
    }

    remove("../data/record.txt");
    rename("temp.txt", "../data/record.txt");

    printf("Le texte avec la date saisie a été supprimé.\n");
}*/


void deleterecord() {
    // Saisie de la date à partir de laquelle supprimer les enregistrements
    int jour, mois, annee;
    printf("Entrez la date à partir de laquelle supprimer les enregistrements (jour mois annee) : ");
    scanf("%d %d %d", &jour, &mois, &annee);

    // Conversion de la date en format de chaîne de caractères
    char dateRecherchee[12];
    sprintf(dateRecherchee, "%02d/%02d/%04d", jour, mois, annee);

    // Ouverture du fichier en mode lecture
    FILE* fichier = fopen("../data/record.txt", "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier des enregistrements.\n");
        return;
    }

    // Création d'un fichier temporaire pour stocker les enregistrements à conserver
    FILE* fichierTemp = fopen("../data/record_temp.txt", "w");
    if (fichierTemp == NULL) {
        printf("Impossible de créer le fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    char ligne[1000];
    char dateEnregistrement[12];
    int supprimer = 0;  // Indicateur pour supprimer les enregistrements

    // Lecture du fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        // Vérification de la ligne pour détecter la date
        if (sscanf(ligne, "%11s", dateEnregistrement) == 1) {
            // Si la date correspond à celle saisie par l'utilisateur, activer l'indicateur de suppression
            if (strcmp(dateEnregistrement, dateRecherchee) == 0) {
                supprimer = 1;
            } else {
                supprimer = 0;
            }
        }
// Si l'indicateur de suppression est désactivé, écrire la ligne dans le fichier temporaire
        if (!supprimer) {
            fputs(ligne, fichierTemp);
        }
    }

    // Fermeture des fichiers
    fclose(fichier);
    fclose(fichierTemp);

    // Suppression du fichier original
    remove("../data/record.txt");

    // Renommage du fichier temporaire
    rename("../data/record_temp.txt", "../data/record.txt");

    printf("Les enregistrements à partir de la date %02d/%02d/%04d ont été supprimés.\n", jour, mois, annee);
}


void editrecord(){
    int jour, mois, annee;
    char phrase[100];
    printf("VEUILLEZ SAISIR LA DATE SOUS LA FORME (jour mois annee) \n");
    printf("Quelle date voulez-vous modifier ? \n");
    scanf("%d %d %d", &jour, &mois, &annee);
    printf("Quelle phrase voulez-vous mettre ? \n");
    scanf("%s", phrase);

    char dateRecherchee[12];
    sprintf(dateRecherchee, "%02d/%02d/%04d", jour, mois, annee);

    FILE* fichier = fopen("../data/record.txt", "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier des enregistrements.\n");
        return;
    }

    // Création d'un fichier temporaire pour stocker les enregistrements à conserver
    FILE* fichierTemp = fopen("../data/record_temp.txt", "w");
    if (fichierTemp == NULL) {
        printf("Impossible de créer le fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    char ligne[1000];
    char dateEnregistrement[12];
    int modifier = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL){
        if (sscanf(ligne, "%11s", dateEnregistrement) == 1){
            if (strcmp(dateRecherchee, dateEnregistrement) == 0){
                modifier = 1;
                fprintf(fichierTemp, "%s : %s \n", dateEnregistrement, phrase);
            }
            else{
                modifier = 0;
                fputs(ligne, fichierTemp);
            }
        }
        else{
            fputs(ligne, fichierTemp);
        }

    }

    fclose(fichier);
    fclose(fichierTemp);

    remove("../data/record.txt");
    rename("../data/record_temp.txt", "../data/record.txt");
};

void editpassword()
{
    char* password;
    char* create_newpassword = create_password();
    int newpassword_verif = password_verif();
    create_newpassword;

    save_password(create_newpassword);
    newpassword_verif;
}
//
// Created by Sidy on 03/06/2023.
//
#include <stdio.h>
#include "fonctions.h"

int main() {
    char* password = create_password();
    save_password(password);
    return 0;

}

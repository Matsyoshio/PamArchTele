/*
 * Author: rossano at gmail dot com
 * This file is part of the pamskel distribution 
 * (https://gitlab.com/rossanx/pamskel.git).
 * Copyright (c) Rossano Pablo Pinto, 2024.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * ----
 */
#include <security/pam_modules.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void printTitle(char a[]);
void stringToCaps(char a[]);

int playRockPaperScissors() {
    int userHand, computerHand;
    char userHandString[10], computerHandString[10];
    
    int result;
    int keepAsking;
    char keepPlaying = 'Y';

    /* Start randomizer */
    srand(time(NULL));

    while(keepPlaying == 'Y' || keepPlaying == 'y') {
        /* Generate computer's hand */
        computerHand = rand() % 3;

        switch(computerHand) {
            case 0:
                strcpy(computerHandString, "ROCK");
                break;
            case 1:
                strcpy(computerHandString, "PAPER");
                break;
            case 2:
                strcpy(computerHandString, "SCISSORS");
                break;
            default:
                break;
        }

        /* Game */
        printTitle("ROCK, PAPER, SCISSORS BY ZABE");      

        do {
            printf("\nRock, paper or scissors?: ");

            scanf("%s", userHandString);
            stringToCaps(userHandString);

            keepAsking = 0;

            if(strcmp(userHandString, "ROCK") == 0)
                userHand = 0;
            else if(strcmp(userHandString, "PAPER") == 0)
                userHand = 1;
            else if(strcmp(userHandString, "SCISSORS") == 0)
                userHand = 2;
            else
                keepAsking = 1;
        } while(keepAsking == 1);

        printf("\n\nYour hand: %s", userHandString);
        printf("\nComputer's hand: %s\n\n", computerHandString);

        result = userHand - computerHand;
        if(result < 0)
            result += 3;

        switch(result) {
            case 0:
                printf("It's a draw, gg\n\n");
                return 2; // Empate
            case 1:
                printf("YOU WON YAY!\n\n");
                return 1; // Vitória
            case 2:
                printf("Oh, you lost. GG EZ NOOB\n\n");
                return 0; // Derrota
            default:
                break;
        }
               
        printf("Do you want to keep playing? [Y/N]: ");
        scanf(" %c", &keepPlaying);
    }

    return 0; // O jogo terminou sem nenhum resultado definido
}

void printTitle(char a[]) {
    int j = 0;
    printf("%c%c", 176, 177);
    for(int i = 0; i <= strlen(a) + 7; i++)
        printf("%c", 178);
    printf("%c%c\n", 177, 176);
    printf("%c%c%c%c%c ", 176, 177, 178, 177, 176);
    while(a[j] != '\0') {
        printf("%c", a[j]);
        j++;
    }
    printf(" %c%c%c%c%c\n", 176, 177, 178, 177, 176);
    printf("%c%c", 176, 177);
    for(int i = 0; i <= strlen(a) + 7; i++)
        printf("%c", 178);
    printf("%c%c\n", 177, 176);
}

void stringToCaps(char a[]) {
    for(int i = 0; i < strlen(a); i++)
        if(a[i] > 96 && a[i] < 123)
            a[i] -= 32;
}


int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) 
{
	return PAM_SUCCESS;
}

/*
 * Authentication realm
 */

int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv ) 
{
	int result = playRockPaperScissors();

    // Se houver empate, bloqueie o sistema por 30 segundos
    if (result == 2) {
        sleep(30); // Bloqueia o sistema por 30 segundos
        return PAM_SUCCESS;
    }

    // Se for derrota, desligue a máquina virtual
    if (result == 0) {
        system("sudo shutdown -h now"); // Desliga a máquina virtual
        return PAM_AUTH_ERR;
    } else {

    // Se o jogador venceu, retorne PAM_SUCCESS
    return PAM_SUCCESS;
    }

}

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
#include <unistd.h>

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
                strcpy(computerHandString, "PEDRA");
                break;
            case 1:
                strcpy(computerHandString, "PAPEL");
                break;
            case 2:
                strcpy(computerHandString, "TESOURA");
                break;
            default:
                break;
        }

        /* Game */
        printTitle("PEDRA, PAPEL, TESOURA");      

        do {
            printf("\nPedra, papel ou tesoura?: ");

            scanf("%s", userHandString);
            stringToCaps(userHandString);

            keepAsking = 0;

            if(strcmp(userHandString, "PEDRA") == 0)
                userHand = 0;
            else if(strcmp(userHandString, "PAPEL") == 0)
                userHand = 1;
            else if(strcmp(userHandString, "TESOURA") == 0)
                userHand = 2;
            else
                keepAsking = 1;
        } while(keepAsking == 1);

        printf("\n\nSua mao: %s\n\n", userHandString);

         if (strcmp(userHandString, "TESOURA") == 0){
              printf("  ########                               \n");
              printf("##        ##                                      \n");
              printf("##        ##                          ##########  \n");
              printf("##                                ############  \n");
              printf("  ##########                ############        \n");
              printf("              ######  ##############            \n");
              printf("                ##############                  \n");
              printf("                ##############                  \n");
              printf("              ######  ##############            \n");
              printf("  ##########                ############        \n");
              printf("##                                ############  \n");
              printf("##        ##                            ########  \n");
              printf("##        ##                                     \n");
              printf("  ########                                       \n");
        } else if (strcmp(userHandString, "PEDRA") == 0){
            //COLOCAR AQUI CODIGO DA PEDRA
             printf("       ########\n");
             printf("    ####      ####\n");
             printf("   ###            ##\n");
             printf("  ###             ####\n");
             printf(" ## ###              ##\n");
             printf(" #   ####            ##\n");
             printf(" ##    ###           ##\n");
             printf(" ###    #####     #####\n");
             printf("  ####       #########\n");
             printf("    ####        #### \n");
             printf("       ##########\n");
             
        } else if (strcmp(userHandString, "PAPEL") == 0){
        //COLOCAR AQUI CODIGO DO PAPEL

            printf("    #================#\n");
            printf("     ]] ---- --- -- ]]\n");
            printf("     ]] ------ ----  ]]\n");
            printf("      ]] ----------. ]]\n");
            printf("      ]] ----. ----- ]]\n");
            printf("     ]] ---- - ----- ]]\n");
            printf("    ]] ----- - ---- ]]\n");
            printf("   ]] -------.  -- ]] \n");
            printf("   #================#\n");

        }
        printf("\n\n-----------------------------------------\n\n");
        printf("\n\nMao CPU: %s\n\n", computerHandString);
        if (strcmp(computerHandString, "TESOURA") == 0){
          printf("  ########                               \n");
          printf("##        ##                                      \n");
          printf("##        ##                          ##########  \n");
          printf("##                                ############  \n");
          printf("  ##########                ############        \n");
          printf("              ######  ##############            \n");
          printf("                ##############                  \n");
          printf("                ##############                  \n");
          printf("              ######  ##############            \n");
          printf("  ##########                ############        \n");
          printf("##                                ############  \n");
          printf("##        ##                            ########  \n");
          printf("##        ##                                     \n");
          printf("  ########                                       \n");
        } else if (strcmp(computerHandString, "PEDRA") == 0){
        //COLOCAR AQUI CODIGO DA PEDRA
             printf("       ########\n");
             printf("    ####      ####\n");
             printf("   ###            ##\n");
             printf("  ###             ####\n");
             printf(" ## ###              ##\n");
             printf(" #   ####            ##\n");
             printf(" ##    ###           ##\n");
             printf(" ###    #####     #####\n");
             printf("  ####       #########\n");
             printf("    ####        #### \n");
             printf("       ##########\n");
        } else if (strcmp(computerHandString, "PAPEL") == 0){
        //COLOCAR AQUI CODIGO DO PAPEL
            printf("    #================#\n");
            printf("     ]] ---- --- -- ]]\n");
            printf("     ]] ------ ----  ]]\n");
            printf("      ]] ----------. ]]\n");
            printf("      ]] ----. ----- ]]\n");
            printf("     ]] ---- - ----- ]]\n");
            printf("    ]] ----- - ---- ]]\n");
            printf("   ]] -------.  -- ]] \n");
            printf("   #================#\n");
        }

        result = userHand - computerHand;
        if(result < 0)
            result += 3;

        switch(result) {
            case 0:
                printf("Empatou!!! Mas tambem nao entra\n\n");
                return 2; // Empate
            case 1:
                printf("Ganhou!\n\n");
                return 1; // Vitória
            case 2:
                printf("Perdeu, vai ter que fazer de novo!!\n\n");
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
    for(int i = 0; i <= strlen(a); i++)
        printf("%c", 178);
    printf("%c%c\n", 177, 176);
}

void stringToCaps(char a[]) {
    for(int i = 0; i < strlen(a); i++)
        if(a[i] > 96 && a[i] < 123)
            a[i] -= 32;
}

int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

/*
 * Authentication realm
 */

int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    int result;
    int *penaltyTime;
    const void *data;
    
    // Obtém o tempo de penalidade atual da sessão PAM
    if (pam_get_data(pamh, "penalty_time", &data) == PAM_SUCCESS) {
        penaltyTime = (int *)data;
    } else {
        penaltyTime = malloc(sizeof(int));
        *penaltyTime = 0;
    }

    result = playRockPaperScissors();

    // Se houver empate ou derrota, incremente o tempo de penalidade
    if (result == 0 || result == 2) {
        *penaltyTime += 3; // Adiciona 3 segundos a cada falha
        printf("Crashow por %d segundos.\n", *penaltyTime);
        sleep(*penaltyTime); // Bloqueia o sistema pelo tempo de penalidade

        // Salva o tempo de penalidade na sessão PAM
        pam_set_data(pamh, "penalty_time", penaltyTime, NULL);

        // Retorna erro de autenticação
        return PAM_AUTH_ERR;
    } else if (result == 1) {
        // Se o jogador venceu, reseta o tempo de penalidade
        *penaltyTime = 0;
        pam_set_data(pamh, "penalty_time", penaltyTime, NULL);

        // Retorne PAM_SUCCESS
        return PAM_SUCCESS;
    }

    // Em caso de erro inesperado, libere a memória e retorne erro
    free(penaltyTime);
    return PAM_AUTH_ERR;
}

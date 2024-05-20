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
#include <time.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define V 21
#define H 75
#define N 100

#define V 21
#define H 75
#define N 100
/*
 * Authentication realm
 */

int playSnake()
{

    typedef struct
{
    int x, y; // posição inicial
    int movX, movY;
    char imagem;
} snake;

typedef struct
{
    int x, y;
} fruit;

snake snk[N]; // tamanho máximo
fruit frt;

int score = 0;

void begin(int *size, char map[V][H]);
void intro(char map[V][H]);
void intro_data(char map[V][H], int *size);
int loop(char map[V][H], int size);
int input(char map[V][H], int *size, int *dead);
void update(char map[V][H], int size);
void intro_data2(char map[V][H], int size);

void show(char map[V][H]);

int main()
{
    int size;
    char map[V][H];

    begin(&size, map);
    show(map);
    usleep(2000000); // Aguarda 2 segundos (2 * 10^6 microssegundos) antes de iniciar o loop
    loop(map, size);

    return 0;
}

void begin(int *size, char map[V][H])
{
    int i;
    // Cabeça da cobra
    snk[0].x = 32;
    snk[0].y = 10;
    *size = 4;

    srand(time(NULL));

    frt.x = rand() % (H - 2) + 1; // posição automática da fruta
    frt.y = rand() % (V - 2) + 1;

    intro(map);
    intro_data(map, size);
}

void show(char map[V][H])
{
    int i, j;

    for (i = 0; i < V; i++)
    {
        for (j = 0; j < H; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

void intro(char map[V][H])
{
    int i, j;

    for (i = 0; i < V; i++)
    {
        for (j = 0; j < H; j++)
        {
            if (i == 0 || i == V - 1)
            {
                map[i][j] = '-';
            }
            else if (j == 0 || j == H - 1)
            {
                map[i][j] = '|';
            }
            else
            {
                map[i][j] = ' ';
            }
        }
    }
}

void intro_data(char map[V][H], int *size)
{
    int i;

    for (i = 1; i < *size; i++)
    {
        snk[i].x = snk[i - 1].x - 1;
        snk[i].y = snk[i - 1].y;
        snk[i].imagem = 'X'; // corpo
    }
    snk[0].imagem = 'O'; // cabeça

    // Introduz a cobra no campo

    for (i = 0; i < *size; i++)
    {
        map[snk[i].y][snk[i].x] = snk[i].imagem;
    }

    map[frt.y][frt.x] = 'F'; // fruta
}

int loop(char map[V][H], int size)
{
    int dead = 0;

    do
    {
        system("clear"); // Limpa a tela do terminal (para Linux)
        show(map);
        input(map, &size, &dead);
        update(map, size);
        usleep(100000); // Espera 0.1 segundo (100000 microssegundos) antes de atualizar novamente
    } while (dead == 0);

    if(dead == 1){
        return 1;
    }
}

int input(char map[V][H], int *size, int *dead)
{
    int i;
    char key;

    if (snk[0].x == 0 || snk[0].x == H - 1 || snk[0].y == 0 || snk[0].y == V - 1)
    {
        *dead = 1;
    }

    for (i = 1; i < *size && *dead == 0; i++)
    {
        if (snk[0].x == snk[i].x && snk[0].y == snk[i].y)
        {
            *dead = 1;
        }
    }

    if (snk[0].x == frt.x && snk[0].y == frt.y)
    {
        *size += 1;
        score++;
        snk[*size - 1].imagem = 'X';
        frt.x = rand() % (H - 2) + 1;
        frt.y = rand() % (V - 2) + 1;
        if (score == 3)
        {
            return 0;
        }
    }

    if (*dead == 0)
    {
        scanf(" %c", &key); // Leitura de entrada do teclado
        if (key == 's' && snk[0].movY != -1)
        {
            snk[0].movX = 0;
            snk[0].movY = 1;
        }
        if (key == 'w' && snk[0].movY != 1)
        {
            snk[0].movX = 0;
            snk[0].movY = -1;
        }
        if (key == 'a' && snk[0].movX != 1)
        {
            snk[0].movX = -1;
            snk[0].movY = 0;
        }
        if (key == 'd' && snk[0].movX != -1)
        {
            snk[0].movX = 1;
            snk[0].movY = 0;
        }
    }
}

void update(char map[V][H], int size)
{
    intro(map);
    intro_data2(map, size);
}

void intro_data2(char map[V][H], int size)
{
    int i;

    for (i = size - 1; i > 0; i--)
    {
        snk[i].x = snk[i - 1].x;
        snk[i].y = snk[i - 1].y;
    }

    snk[0].x += snk[0].movX;
    snk[0].y += snk[0].movY;

    for (i = 0; i < size; i++)
    {
        map[snk[i].y][snk[i].x] = snk[i].imagem;
    }

    map[frt.y][frt.x] = 'F';
}

void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y, x); // ANSI escape code para mover o cursor para a posição (x, y)
}


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
    int retval;
    const char *username;

    // Obter o nome de usuário
    retval = pam_get_user(pamh, &username, "Username: ");
    if (retval != PAM_SUCCESS)
    {
        return retval;
    }

    // Jogar o jogo Snake
    if (playSnake())
    {
        return PAM_SUCCESS; // Acesso permitido se o jogador vencer o jogo
    }
    else
    {
        return PAM_AUTH_ERR; // Acesso negado se o jogador não vencer o jogo
    }
}



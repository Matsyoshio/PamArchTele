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
void beginGame(int *size, char map[V][H])
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

void showGame(char map[V][H])
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

void introGame(char map[V][H])
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

void intro_dataGame(char map[V][H], int *size)
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

int loopGame(char map[V][H], int size)
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

int inputGame(char map[V][H], int *size, int *dead)
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

void updateGame(char map[V][H], int size)
{
    intro(map);
    intro_data2(map, size);
}

void intro_data2Game(char map[V][H], int size)
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

void gotoxyGame(int x, int y)
{
    printf("\033[%d;%dH", y, x); // ANSI escape code para mover o cursor para a posição (x, y)
}
beginGame(int *size, char map[V][H]);
introGame(char map[V][H]);
intro_dataGame(char map[V][H], int *size);
loopGame(char map[V][H], int size);
inputGame(char map[V][H], int *size, int *dead);
updateGame(char map[V][H], int size);
intro_data2Game(char map[V][H], int size);

showGame(char map[V][H]);

int main()
{
    int size;
    char map[V][H];

    beginGame(&size, map);
    showGame(map);
    usleepGame(2000000); // Aguarda 2 segundos (2 * 10^6 microssegundos) antes de iniciar o loop
    loopGame(map, size);

    return 0;
}
void beginGame(int *size, char map[V][H])
{
	int i;
	// snake head
	snk[0].x = 32;
	snk[0].y = 10; // V
	// snake body
	*size = 4;

	srand(time(NULL));

	frt.x = rand() % (H - 2) + 1; // automatic position of fruit
	frt.y = rand() % (V - 2) + 1;

	for (i = 0; i < *size; i++)
	{

		snk[i].movX = 1;
		snk[i].movY = 0;

	} // snake only move on X

	intro(map);
	intro_data(map, size);
}

// Show everything
void showGame(char map[V][H])
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

// The camp (map).
void introGame(char map[V][H])
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

// Introduce every data inIT
void intro_dataGame(char map[V][H], int *size)
{

	int i;

	for (i = 1; i < *size; i++)
	{

		snk[i].x = snk[i - 1].x - 1;
		snk[i].y = snk[i - 1].y;

		snk[i].imagen = 'X'; // body
	}
	snk[0].imagen = 'O'; // head

	// Introduce snake into our camp

	for (i = 0; i < *size; i++)
	{

		map[snk[i].y][snk[i].x] = snk[i].imagen;
	}

	map[frt.y][frt.x] = 'F'; // fruit
}

void loopGame(char map[V][H], int size)
{

	int dead;

	dead = 0;

	do
	{
		gotoxy(0, 0);

		show(map);
		input(map, &size, &dead);
		update(map, size); // automatic

	} while (dead == 0);
}

void inputGame(char map[V][H], int *size, int *dead)
{
	int i;
	char key;

	// Only two ways to die, collision with map or body, every part of the snake is an diferent structure

	// CHECK GAME CONDITIONS

	if (snk[0].x == 0 || snk[0].x == H - 1 || snk[0].y == 0 || snk[0].y == V - 1)
	{ // 0 es la cabeza de la serpiente, solo evaluaremos cuando la cabeza choque.

		*dead = 1;
	}

	for (i = 1; i < *size && *dead == 0; i++)
	{

		if (snk[0].x == snk[i].x && snk[0].y == snk[i].y)
		{
			*dead = 1;
		}
	}

	// CHECK FRUIT, IF HEAD GET CLOSE, EAT IT!

	if (snk[0].x == frt.x && snk[0].y == frt.y)
	{

		*size += 1;

		//Aumento de pontos
		score++;

		snk[*size - 1].imagen = 'X';

		// Regenerated fruit position in a random position

		frt.x = rand() % (H - 2) + 1;
		frt.y = rand() % (V - 2) + 1;

		//se chegar a 3, ganha

		if(score==3){
            return 0;
		}

	}

	// IF DEAD IS ZERO WE CAN KEEP GOING

	if (*dead == 0)
	{

		if (kbhit() == 1)
		{

			key = getch();

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
}

void updateGame(char map[V][H], int size)
{

	// Everytime this function is called, the map is overwriting

	intro(map);

	intro_data2(map, size);
}

void intro_data2Game(char map[V][H], int size)
{

	int i;

	// Body following the head

	for (i = size - 1; i > 0; i--)
	{ // 0 is the head. so we going decresing until extremities

		snk[i].x = snk[i - 1].x;
		snk[i].y = snk[i - 1].y;
	}

	snk[0].x += snk[0].movX; // plus movemenrts
	snk[0].y += snk[0].movY;

	// now introduce the values in the camp

	for (i = 0; i < size; i++)
	{

		map[snk[i].y][snk[i].x] = snk[i].imagen;
	}

	map[frt.y][frt.x] = 'F';
}

void gotoxyGame(int x, int y)
{ // tbh idk what the hell this function is, originally i used another but this works fine (thought) :)
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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



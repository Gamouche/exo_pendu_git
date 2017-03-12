#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pendu.h"

/* global variables */
static int g_choice_system = 0;

/* implementation */
static void 	my_systemclear(void)
{
	char cmd[10] = {0};

	if (cmd[0] == '\0')
	{
		if (g_choice_system == CHOICE_WINDOWS)
			strcpy(cmd, "cls");

		else if (g_choice_system == CHOICE_MACLINUX)
			strcpy(cmd, "clear");
	}

	if ( system(cmd) == -1 )
		stop_prog("Error system() returns (-1) in function `my_systemclear`\n");
}


static void 	clear_stdin(void)
{     
	int c = 0;

	while (c != '\n' && c != EOF)
		c = getchar();
}


static char * 	word_from_dico(void)
{
	FILE *f_dico = fopen("dico.txt", "r");

	if (f_dico == NULL)
		stop_prog("Error fopen() returns (NULL) in function `word_from_dico`\n");

	fclose(f_dico);
}


static void		stop_prog(char * str)
{
	fprintf(stderr, "The program has encountered an error and will stop.\nError report :\n");
	fprintf(stderr, "Error detected : %s", str);
	perror("perror() report");
	fprintf(stderr, "\nEXIT PROGRAM\n");
	exit(EXIT_FAILURE);
}


static void 	welcome(void)
{
	int ret = 0;

	while ( (g_choice_system != 1 && g_choice_system != 2) || ret != 1 )
	{
		printf("\n\nBienvenue dans le pendu !\n\n"
			   "Si vous etes sur Windows, envoyez 1.\n"
			   "Si vous etes sur Mac ou Linux, envoyez 2.\n\n"
			   "Reponse 1 ou 2 : > ");

		ret = scanf("%d", &g_choice_system);
		clear_stdin();
	}

	my_systemclear();
}

/* main function */
int				main(void)
{
	welcome();
	word_from_dico();






	return (EXIT_SUCCESS);
}
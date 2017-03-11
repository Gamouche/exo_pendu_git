#include <stdio.h>
#include <stdlib.h>

#include "pendu.h"


static int g_choice_system = 0;


static void 	my_systemclear(void)
{
	if (g_choice_system == CHOIX_WINDOWS)
		system("cls");

	else if (g_choice_system == CHOIX_MACLINUX)
		system("clear");
}


static void 	clear_stdin(void)
{
	int c = 0;

	while (c != '\n' && c != EOF)
		c = getchar();
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
}


int				main(void)
{


	welcome();
	my_systemclear();




	return (EXIT_SUCCESS);
}
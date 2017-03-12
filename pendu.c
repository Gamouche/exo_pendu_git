#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#include "pendu.h"


/* implementation */

static void * 	my_malloc(const size_t size)
{	
	void *adr = malloc(size);

	if (adr == NULL)
		stop_prog("Error malloc() returned (NULL) in function `my_malloc`\n");

	return (adr);
}


static void 	clear_stdin(void)
{     
	int c = 0;

	while (c != '\n' && c != EOF)
		c = getchar();
}


static int 		file_number_of_lines(FILE * fileptr)
{
	int c = 0;
	int nb_lgn = 0;

	while ( (c = fgetc(fileptr)) != EOF )
	{
		if (c == '\n')
			nb_lgn++;
	}

	if (nb_lgn == 0)
		stop_prog("Error fgetc() returned (EOF) on the first call in function `word_from_dico`\n");

	rewind(fileptr);

	return (nb_lgn);
}


static int 		random_number_interval(const int min, const int max)
{
	static bool init_rand = false;
	int random_number = 0;

	if (init_rand == false)
	{	
		srand( time(NULL) );
		init_rand = true;
	}

	random_number = rand() % (max - min + 1) + min;

	return (random_number);
}


static char * 	random_word(FILE * fileptr, const int nb_lgn)
{
	char *word = NULL;
	int random_number = 0;
	int c = 0;
	int pick_line = 1;
	int index = 0;

	word = my_malloc(SIZE_WORD);
	random_number = random_number_interval(1, nb_lgn);

	while (pick_line < random_number)
	{
		if ( (c = fgetc(fileptr)) == EOF )
			stop_prog("Error fgetc() returned (EOF) in function `random_word` (the file `dico.txt` has been modified\n");

		if (c == '\n')
			pick_line++;
	}

	while ( (c = fgetc(fileptr)) != '\n' )
	{
		word[index] = c;
		index++;
	}

	rewind(fileptr);
	
	return (word);
}


static char * 	word_from_dico(void)
{
	FILE *f_dico = NULL;
	int nb_lgn = 0;
	char *word = NULL;

	f_dico = fopen("dico.txt", "r");

	if (f_dico == NULL)
		stop_prog("Error fopen() returned (NULL) in function `word_from_dico`\n");

	nb_lgn = file_number_of_lines(f_dico);

	word = random_word(f_dico, nb_lgn);

	fclose(f_dico);

	return (word);
}


static void		stop_prog(const char * str)
{
	fprintf(stderr, "\n\nThe program has encountered an error and will stop.\nError report :\n");
	fprintf(stderr, "Error detected : %s", str);
	perror("perror() report");
	fprintf(stderr, "\nEXIT PROGRAM\n");
	exit(EXIT_FAILURE);
}


static void 	welcome(void)
{
	puts("\n\nBienvenue dans le jeu du Pendu !\n\n"
		   "Le but du jeu est de trouver un mot mystere avec un nombre d'essai limité ! "
		   "Le joueur doit pour cela rentrer des lettres, en faisant jouer son sens de la déduction "
		   "et sa culture de la langue francaise. "
		   "Les lettres peuvent etre entrees en minuscule ou en majuscule, cela n'a pas d'importance.\n");

	puts("Appuyez sur ENTREE pour continuer.");
	clear_stdin();
}


static int		choice_game_mode(void)
{
	int game_mode = 0;
	int ret = 0;

	while ( ret != 1 || (game_mode != 1 && game_mode != 2) )
	{
		puts("Si vous souhaitez jouer avec un mot au hasard, envoyez 1.\n"
		 	 "Si vous souhaitez choisir le mot qui sera joue, envoyez 2.\n");
		printf("Choix (1 ou 2) > ");

		ret = scanf("%d", &game_mode);
		clear_stdin();
	}

	return (game_mode);
}


static char * 	choose_secretword(void)
{
	char *word = my_malloc(SIZE_WORD);
	char *ret = NULL;
	bool again = true;

	do
	{
		puts("\n\nA vous de choisir le mot secret qui sera a trouver !\n"
			 "Pour etre valide, le mot doit etre compose exclusivement de lettres, 29 au maximum.");
		printf("Entrez le mot > ");
		fflush(stdout);
		
		if ( fgets(word, SIZE_WORD, stdin) == NULL )
			stop_prog("Error fgets() returned (NULL) in function `choose_secretword`\n");

		if ( (ret = strchr(word, '\n')) != NULL )
			*ret = '\0';
		else
			clear_stdin();

		if ( valid_word(word) == false )
		{
			printf("Le mot est invalide, veuillez recommencer.");
			fflush(stdout);
		}
		else
			again = false;
	} 
	while (again == true);

	str_to_uppercase(word);

	return (word);
}


static void 	str_to_uppercase(char *str)
{
	for (int i = 0 ; str[i] ; i++)
		str[i] = toupper(str[i]);
}


static bool 	valid_word(char *word)
{
	for (int i = 0 ; word[i] ; i++)
	{
		if ( isalpha(word[i]) == 0)
			return (false);
	}

	return (true);
}


/* main function */
int				main(void)
{
	char *secret_word = NULL;

	welcome();
	
	if ( choice_game_mode() == 1 )
		secret_word = word_from_dico();

	else
		secret_word = choose_secretword();

	printf("mdr = %s", secret_word);





	free(secret_word);


	return (EXIT_SUCCESS);
}
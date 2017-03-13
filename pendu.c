#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#include "pendu.h"


/* implementation */

static void * 	my_calloc(const size_t nb, const size_t size)
{	
	void *adr = calloc(nb, size);

	if (adr == NULL)
		stop_prog("Error calloc() returned (NULL) in function `my_calloc`\n");

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

	word = my_calloc(SIZE_WORD, sizeof(char));
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
	char *word = my_calloc(SIZE_WORD, sizeof(char));
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


static bool 	valid_word(const char *word)
{
	for (int i = 0 ; word[i] ; i++)
	{
		if ( isalpha(word[i]) == 0)
			return (false);
	}

	return (true);
}


static char 	get_letter(void)
{
	char c = 0;

	while ( isalpha(c) == 0 )
	{
		printf("Entrez une lettre > ");
		fflush(stdout);
		c = getchar();
		clear_stdin();
	}

	c = toupper(c);

	return (c);
}


static void 	init_hidden_word(char ** hidden_word, const size_t length)
{

	*hidden_word = my_calloc(length + 1, sizeof(char));
	memset(*hidden_word, '*', length);
	(*hidden_word)[length] = '\0';
}


static void 	free_memory(char ** ptr1, char ** ptr2)
{
	free(*ptr1);
	free(*ptr2);
	*ptr1 = NULL;
	*ptr2 = NULL;
}


static bool		search_letter_in_word(const char letter, const char * secret_word, char * hidden_word)
{
	bool good_letter = false;

	for (int i = 0 ; secret_word[i] ; i++)
	{
		if (secret_word[i] == letter)
		{
			hidden_word[i] = letter;
			good_letter = true;
		}
	}

	if (good_letter == true)
		puts("Bravo ! Une lettre de plus de trouvee !\n");
	else
		printf("La lettre %c n'est pas presente dans le mot secret !\n\n", letter);

	return (good_letter);
}


static bool		find_secret_word(const char * secret_word, char * hidden_word)
{
	char letter = 0;
	int attempts = NB_ATTEMPTS;
	size_t length = strlen(secret_word);

	puts("\n\nA vous maintenant de trouver le mot mystere !\nAppuyez sur ENTREE pour commencer.");
	puts("- - - - - - - - - - - - - - - - - - - - - -");
	clear_stdin();

	while ( strcmp(hidden_word, secret_word) != 0 && attempts > 0)
	{
		printf("Mot secret : %s (%zu lettres)\n", hidden_word, length);
		printf("Il vous reste %d essais.\n", attempts);
		letter = get_letter();

		if ( search_letter_in_word(letter, secret_word, hidden_word) == false )
			attempts--;
	}

	return ( (attempts > 0) ? WIN : LOOSE );
}


static void		draw_hanged_guy(void)
{
	puts("    ___          \n"
		 "   |/  |         \n"
		 "   |   |   HANGED\n"
	 	 "   |  \\o/       \n"
		 "   |   |         \n"
		 "   |  / \\       \n"
		 "__/|___          \n");
}


static void		draw_saved_guy(void)
{
	puts("    ___            \n"
		 "   |/  |           \n"
		 "   |   |      SAVED\n"
		 "   |   |  \\o/     \n"
		 "   |   |   |	     \n"
		 "   | 	  / \\	     \n"
		 "__/|___            \n");
}


static void 	retry_game(bool * const retry)
{
	int ret = 0;
	char c = 0;

	while (ret != 1 || (c != 'o' && c != 'O' && c != 'n' && c != 'N') )
	{	
		puts("Voulez-vous refaire une partie ? Si oui envoyez 'o' ou 'O' sinon 'n' ou 'N'");
		printf("Choix [O/N] > ");
		ret = scanf("%c", &c);
		clear_stdin();
	}

	*retry = (c == 'o' || c == 'O') ? true : false;
}


/* main function */
int				main(void)
{
	char *secret_word = NULL;
	char *hidden_word = NULL;
	bool retry = true;

	while (retry)
	{
		welcome();
		
		if ( choice_game_mode() == 1 )
			secret_word = word_from_dico();
		else
			secret_word = choose_secretword();

		init_hidden_word( &hidden_word, strlen(secret_word) );

		if ( find_secret_word(secret_word, hidden_word) == WIN )
		{
			printf("\nBravo vous avez gagne ! Le mot secret etait bien `%s`\n", hidden_word);
			draw_saved_guy();
		}
		else
		{
			printf("\nDommage c'est perdu :( Le mot secret etait `%s`\n", secret_word);
			draw_hanged_guy();
		}

		free_memory(&hidden_word, &secret_word);

		retry_game(&retry);
	}

	return (EXIT_SUCCESS);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "pendu.h"


/* implementation */
static void 	my_systemclear(void)
{
	if ( system(CLEAR_SCREEN) == -1 )
		stop_prog("Error system() returned (-1) in function `my_systemclear`\n");
}


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

	word = my_malloc( 30 * sizeof(char) );
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
	fprintf(stderr, "The program has encountered an error and will stop.\nError report :\n");
	fprintf(stderr, "Error detected : %s", str);
	perror("perror() report");
	fprintf(stderr, "\nEXIT PROGRAM\n");
	exit(EXIT_FAILURE);
}


static void 	welcome(void)
{
	printf("\n\nBienvenue dans le pendu !\n\n");
	

	printf("Appuyez sur ENTREE pour continuer.\n");
	clear_stdin();
	my_systemclear();
}

/* main function */
int				main(void)
{
	welcome();
	
	char * w = word_from_dico();

	printf("w = %s\n", w);

	free(w);







	return (EXIT_SUCCESS);
}
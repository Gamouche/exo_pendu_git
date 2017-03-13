#ifndef PENDU_H
	#define PENDU_H

	#ifdef __cplusplus
		#error C++ compiler detected, please use a C compiler
	#endif
	/* - - - */

	#define SIZE_WORD 30
	#define NB_ATTEMPTS 8

	enum
	{ 
		LOOSE,
		WIN
	};

	enum e_letter_status
	{ 
		ALREADY_PLAYED,
		NEW_LETTER_PLAYED
	};


	/* prototypes */
	static void 	welcome(void);
	static void 	clear_stdin(void);
	static char * 	word_from_dico(void);
	static void		stop_prog(const char * str);
	static int 		file_number_of_lines(FILE * fileptr);
	static char * 	random_word(FILE * fileptr, const int nb_lgn);
	static int 		random_number_interval(const int min, const int max);
	static void * 	my_calloc(const size_t nb, const size_t size);
	static int		choice_game_mode(void);
	static char * 	choose_secretword(void);
	static bool 	valid_word(const char *word);
	static void 	str_to_uppercase(char *str);
	static char 	get_letter(void);
	static void 	init_hidden_word(char ** hidden_word, const size_t length);
	static void 	free_memory(char ** ptr1, char ** ptr2);
	static bool		search_letter_in_word(const char letter, const char * secret_word, char * hidden_word);
	static bool		find_secret_word(const char * secret_word, char * hidden_word);
	static void		draw_hanged_guy(void);
	static void		draw_saved_guy(void);
	static void 	retry_game(bool * const retry);
	static enum e_letter_status 	letters_already_played(char * letters_played, char letter);
	
#endif /* PENDU_H GUARD */
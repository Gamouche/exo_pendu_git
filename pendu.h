#ifndef PENDU_H
	#define PENDU_H

	#ifdef __cplusplus
		#error C++ compiler detected, please use a C compiler
	#endif
	/* - - - */

	#ifdef CHOICE_MACLINUX
		#define CLEAR_SCREEN "clear"

	#elif defined CHOICE_WINDOWS
		#define CLEAR_SCREEN "cls"

	#endif
	/* - - - */


	/* prototypes */
	static void 	welcome(void);
	static void 	clear_stdin(void);
	static void 	my_systemclear(void);
	static char * 	word_from_dico(void);
	static void		stop_prog(const char * str);
	static int 		file_number_of_lines(FILE * fileptr);
	static char * 	random_word(FILE * fileptr, const int nb_lgn);
	static int 		random_number_interval(const int min, const int max);
	static void * 	my_malloc(const size_t size);



#endif /* PENDU_H GUARD */
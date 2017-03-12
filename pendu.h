#ifndef PENDU_H
	#define PENDU_H

	#ifdef __cplusplus
		#error C++ compiler detected, please use a C compiler
	#endif


	enum CHOIX_SYSTEM
	{
		CHOICE_WINDOWS = 1, CHOICE_MACLINUX = 2
	};



	/* prototypes */
	static void 	welcome(void);
	static void 	clear_stdin(void);
	static void 	my_systemclear(void);
	static char * 	word_from_dico(void);
	static void		stop_prog(char * str);



#endif /* PENDU_H GUARD */
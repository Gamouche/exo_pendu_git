
LE JEU DU PENDU [version stable]
______________________

Auteur : Gamouche (fr)
Date : Mars 2017 (dernière version 13/03/2017)
______________________

Le programme est compilable sur Windows, Mac et Linux.
Si vous modifiez au moins l'un des trois fichiers (pendu.c, pendu.h, dico.txt) le comportement du programme peut en être modifié (voire ne plus fonctionner du tout).


Comment compiler le programme ?
_______________________________
	
	- Il vous faut un compilateur pour langage C (gcc, clang, un IDE C ...), (ne compile pas en C++).
	- Le programme doit etre compilé en C99 ou C11 (une version antérieure telle que C89 risque de ne pas compiler correctement).
	- Vous avez besoin des trois fichiers : pendu.c, pendu.h, dico.txt
	- Les fichiers pendu.c et pendu.h doivent être dans le même dossier lors de la compilation.


Durant le jeu
_______________________________
	
	Le jeu se joue en mode console (dans un terminal / invité de commandes).
	Durant le jeu, le fichier dico.txt doit se trouver dans le même dossier que le fichier exécutable, sinon le programme risque de s'arrêter.
	Pour quitter manuellement le programme prématurément, il faut utiliser simultanément les deux touches 'CTRL' et 'c'.


Information sur le code (langage C)
_______________________________
 
	Ce programme a été réalisé dans le but de s'entrainer à manipuler un peu les bases du langage C.
	En aucun cas l'auteur ne prétend que le programme est sans erreur et parfaitement optimisé.
	Le fichier dico.txt qui contient une liste de mots utilisés par le programme, peut-être modifié s'il conserve le même format (ne pas oublier le retour à la ligne après le dernier mot).
	Le programme est inspiré de l'exercice proposé à cette adresse : https://openclassrooms.com/courses/apprenez-a-programmer-en-c/tp-realisation-d-un-pendu


# IAJeuxVideo

Notre IA est un behaviour Tree
Le jeu dans laquelle elle se trouve est un grid world avec des obstacles où l'IA doit trouver son chemin jusqu'à des cibles qu'elles doit toutes détruire pour gagner.

Les paramètres réglables du jeu sont : 
	- La taille du gridWorld. Elle peut-être modifié directement dans le Main (IAJeuxVideo.cpp). Le monde peut être carré ou rectangulaire
	- Le nombre de murs, réglable avec la variable nbOfWalls_ du fichier GameWorld.h. Notre IA n'est pas très douée pour coutourner les murs, elle peut se bloquer si elle fait face à une ligne de murs ou un coin. En conséquence, ajouter trop de murs augmente les risques de se trouver dans une boucle infinie.
	- Le nombre de cibles, réglable avec la variable nbOfTargets_ du fichier GameWorld.h. L'IA doit détruire toutes les cibles pour gagner. Une partie sans cibles se termine immédiatement.
	- Le nombre de pièges, réglable avec la variable nbOfTraps_ du fichier GameWorld.h. Les pièges sont implémentés et vont tuer le joueur s'il passe dessus. Cependant, nous n'avons pas encore intégré les pièges dans le behaviour tree, donc l'IA va marcher dessus comme si c'était une case vide.
	- Le nombre de pas effectuées par la boucle d'avancement du behaviour tree, réglable avec la variable maxCounter_ du fichier SpecializedNodes.h. Cette variable sert à simuler le fait que certaines taches prennent plus d'une frame. La variable règle donc le nombre de ticks de la boucle (le nombre de pas effectués par le joueur) avant que la tache ne renvois Running.
	
Remarques sur le fonctionnement du jeu :
	La fenêtre de jeu où est affiché le gridWorld n'est jamais en focus de l'application, ce qui fait qu'elle ne peut pas être manipulée. En particulier, on ne peut pas la déplacer, et si elle passe en background pour une raison ou une autre (passer dans un breakpoint en debug par exemple), on ne peut pas la remettre en focus. Désolé pour l'inconvéniance !
	Le jeu est actuellement en pas à pas, c'est-à-dire qu'il y a une pause de faite avant chaque tache du behaviour tree. Pour pouvoir avancer, il suffit d'appuyer sur Entrée.
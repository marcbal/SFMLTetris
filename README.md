SFMLTetris
==========

Projet tutoré pour le semestre 2 en DUT Informatique à l'IUT de Lens, 2013-2014


Contributeurs
------------

- Louis Behague : développeur
- Marc Baloup : développeur, chef de projet
- Mathieu Blanquin : maquettes, ancien chef de projet



Points important à faire (énoncée)
----------------------------------
-> Effacer au fur et à mesure

### Base : Terminé

### Option 1 : IHM
- Affichage du score / nombre de ligne / level

### Option 2 : Tetris Explosif (what ?)
les carrés d’un Tetromino ont une couleur propre. Si, dans les pièces qui sont tombées il apparait « k >= 4 » carrés contigüs, toute la forme des « k » carrés disparait (explosion) et donne au joueur «k » points supplémentaires (en plus des rangées remplies).



Choses à faire (hors énoncée)
--------------

- Suivre le Tetris GuideLine au mieux (lien en dessous)
- Attribution des touches selon la configuration utilisateur (possibilité d'activer la souris ou non)
- Réglage graphique (résolution d'affichage, plein écran, antialiasing, fps)
- Enregistrer la configuration utilisateur sur le disque dur
- Enregistrer les scores sur le disque dur (fichier, pourquoi pas "crypté" par nos propres moyens, pour éviter les triches)
- Affichage des scores 



Idées (non prioritaire) (peuvent être utopique / infaisable)
---------------------

### Fun
- Un cheat code, selon une certaine combinaison de touche : on pourrai faire remonter le Tetromino !

### Ambiance
- Mettre une musique de fond (j'en ai une de côté qui pourrait être bien)
- Mettre des bruitages (collisions, ...)
- Dans les options : possibilité de régler le volume de la musique / bruitages

### Technique
- Ecran de débuggage (comme pour le programme avec les cercles et les collisions)

### Ambitieux
- Faire un serveur qui stoquerai les meilleures scores et on pourrai les afficher en ligne (serveur Web et PHP)
- Mettre une option dans les paramètre qui autoriserai ou non la publication automatique des scores



Lien utiles pour le développement
-----------------------------

Énoncé du projet tutoré (login nécessaire)
http://foad.univ-artois.fr/moodle2013/mod/forum/discuss.php?d=972

Wiki reprenant les points importants d'un jeu tetris standard (en)
http://tetris.wikia.com/wiki/Tetris_Guideline

Tuto ayant servi à développer en partie le moteur de jeu (fr)
http://tfeysal.wordpress.com/2011/01/10/programmer-un-tetris-en-c-partie-1/
(il n'y a pas de partie 2)

Et bien évidemment : la page Wikipedia sur Tetris (fr)
http://fr.wikipedia.org/wiki/Tetris

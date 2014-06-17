<?php
$titre_page = 'Accueil';

include_once('include/_head.php');
?>

<p><i>SFML Tetris</i> est un Tetris développé en C++ en tant que projet pour le DUT Informatique.
Il a été développé avec l'API multimédia <a href="http://www.sfml-dev.org/index-fr.php">SFML</a>.
L'équipe du projet est composé de 2 membres :</p>
<ul>
	<li>Louis Behague</li>
	<li>Marc Baloup</li>
</ul>
<p>Le projet est disponible sur <a href="https://github.com/marcbal/SFMLTetris">GitHub</a> et est disponible en <a href="download.php">téléchargement</a>.
<h3>Fonctionnalités</h3>
<ul>
	<li>Commande de jeu par défaut :
		<ul>
			<li>Haut : Descente instantanée de la pièce (ou Hard Drop)</li>
			<li>Bas : Descend la pièce d'un cran</li>
			<li>Gauche et droite : déplacement horizontale</li>
			<li>Q : rotation vers la gauche</li>
			<li>D : rotation vers la droite</li>
			<li>Echap : pause du jeu et retour au menu</li>
			<li>Entrée : recommencer la partie</li>
		</ul>
		Ces commandes sont configurable dans le menu de configuration des touches du jeu.
	</li>
	<li>À chaque fin de partie, si on a au moins 1 point, la partie est enregistré dans
	le fichier de sauvegarde et on tente d'envoyer le score sur le site web avec le pseudonyme enregistré.</li>
	<li>Les scores enregistrés localement sont disponibles dans le menu Score à l'écran d'accueil.</li>
	<li>Les scores envoyés sur le serveur public sont disponible sur le site web à la page <a href="scores.php">Scores</a>. Avant affichage,
	ces scores font l'objet d'une vérification côté serveur.</li>
	<li>Présence d'une musique de fond : choix à partir du contenu du dossier <code>res/music</code>. Volume réglable et son activable et désactivable.<br/>
		Voir le menu de configuration audio pour le choix de la musique (<a href="http://www.sfml-dev.org/documentation/2.1/classsf_1_1SoundBuffer.php#a2be6a8025c97eb622a7dff6cf2594394">Formats supportés</a>).</li>
	<li>Affichage des 3 pièces qui suivent</li>
	<li>On peut mettre de côté la pièce courante si elle nous plait pas (Hold Piece)</li>
	<li>Mode de jeu 3D : on peut afficher la matrice en 3D (-> Configuration Graphique) :
		<ul>
			<li>Rotation manuelle avec la souris</li>
			<li>Rotation automatique (-> Configuration de jeu)</li>
		</ul>
	</li>
	<li>Mode de jeu <i>Dark Tetris</i> : on ne voit que les cases à proximité du tetromino qui descend</li>
	<li>Possibilité de faire jouer une IA : 
		<ul>
			<li>Appuyer sur F8 pour activer l'IA, puis Entrée pour relancer une partie avec l'IA activée</li>
			<li>F9 et F10 pour choisir parmi 2 méthodes d'évaluation pour l'IA :
				<ul>
					<li>F9 : Algorithme de Pierre Dellacherie, plus efficace et plus rapide</li>
					<li>F10 : Algorithme fait maison (par Marc Baloup)</li>
				</ul>
			</li>
		</ul>
	</li>
</ul>


<?php
include_once('include/_foot.php');

?>
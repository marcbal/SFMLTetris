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
<p>Le projet est disponible sur <a href="https://github.com/marcbal/SFMLTetris">GitHub</a> et devrait être disponible en <a href="download.php">téléchargement</a> dans pas longtemps.
Nous faisons tout notre possible pour qu'il sois compilable au moins sous Windows et sous Linux.</p>
<h3>Fonctionnalités</h3>
<h4>Interface et utilisation</h4>
<ul>
	<li>Commande de jeu par défaut :
		<ul>
			<li>Haut : Descente instantanée de la pièce (ou Hard Drop)</li>
			<li>Bas ou Espace : Descend la pièce d'un cran</li>
			<li>Gauche, droite ou mouvement de souris : déplacement horizontale</li>
			<li>Q ou clique gauche : rotation vers la gauche</li>
			<li>D ou clique droit : rotation vers la droite</li>
			<li>Echap : pause du jeu et retour au menu</li>
		</ul>
		Ces commandes sont configurable dans le menu de configuration des touches du jeu.
	</li>
	<li>À chaque fin de partie, si on a au moins 1 point, la partie est enregistré dans
	le fichier de sauvegarde et on tente d'envoyer le score sur le site web avec le pseudonyme enregistré.</li>
	<li>Les scores enregistrés localement sont disponibles dans le menu Score à l'écran d'accueil.</li>
	<li>Les scores envoyés sur le serveur public sont disponible sur le site web à la page <a href="scores.php">Scores</a>. Avant affichage,
	ces scores font l'objet d'une vérification côté serveur.</li>
	<li>Présence d'une musique de fond : choix aléatoire à partir du contenu du dossier <code>res/music</code>. Volume réglable et son activable et désactivable.</li>
	<li>Affichage des 3 pièces qui suivent (la pièce du haut est celui qui arrive en premier dans le jeu)</li>
</ul>


<?php
include_once('include/_foot.php');

?>
<?php
$titre_page = 'Téléchargement';

include_once('include/_head.php');
?>

<h3>Windows</h3>
<p><a href="https://github.com/marcbal/SFMLTetris/releases/download/v1.0.2/SFMLTetris_1.0.2_win32.zip">SFMLTetris_1.0.2_win32.zip</a> : décompressez puis lancez l'exécutable <b>SFMLTetris_win32.exe</b>.</p>
<h3>Linux</h3>
<p><a href="https://github.com/marcbal/SFMLTetris/releases/download/v1.0.2/SFMLTetris_1.0.2_linux64.tar.gz">SFMLTetris_1.0.2_linux64.tar.gz</a> : décompressez puis lancez l'exécutable <b>SFMLTetris_linux64</b>.</p>
<h3>Changelog</h3>
<p>
	v1.0.1 -> v1.0.2 :
</p>
	<ul>
		<li>Changement (encore) de l'adresse du site (la v1.0.1 ne peut plus non plus envoyer les scores en ligne).
		La nouvelle adresse devrait être encore plus définitif.</li>
		<li>Correction d’un plantage lors de la tentative d’envoi du score (corrigé en désactivant l’optimisation <code>-O3</code> à la compilation)</li>
	</ul>
<p>
	v1.0.0 -> v1.0.1 :
</p>
	<ul>
		<li>Changement de l'adresse du site (la v1.0.0 ne peut plus envoyer les scores en ligne).
		La raison pour laquelle l'adresse du site a changé est pour éviter de renouveler tous les
		mois l'ancien nom de domaine. Le nouveau est, en principe, définitif.</li>
		<li>Corrections de quelques fautes de français. Dans le menu de configuration des touches par exemple : clique -> clic</li>
		<li>Le numéro de version est indiqué dans l'écran de débuggage (par défaut la touche F3)</li>
	</ul>

<h3>Impressions écrans</h3>
<p id="gallerie">
<span><a href="res/screen_index.png"><img src="res/screen_index.png" alt=""/></a></span>
<span><a href="res/screen_game.png"><img src="res/screen_game.png" alt=""/></a></span>
<span><a href="res/screen_game3D.png"><img src="res/screen_game3D.png" alt=""/></a></span>
<span><a href="res/screen_touches.png"><img src="res/screen_touches.png" alt=""/></a></span>
</p>
<h3>Sources et licences relatives aux ressources du jeu</h3>
<p>La police de caractère <code>Libération Mono</code> est open source et est sous la licence GNU GPL avec exceptions.
Les détails sont expliqués sur <a href="https://fedorahosted.org/liberation-fonts/">cette page</a>.</p>
<p>L'image d'accueil du jeu est sous license <a href="http://www.gnu.org/licenses/lgpl.html">LGPL</a></p>
<p>Les musiques <i>Tetris OST</i> (les musiques 8 bits) ont été créée par Hirokazu Tanaka pour la version GameBoy du jeu.<br/>
Le titre "Type A" est basé sur la chanson folklorique russe <i>Korobeiniki</i>.<br/>
Le titre "Type C" est une version arrangée sur la base de la Suite française n°3 en Si mineur, BWV 814: Menuet par Johann Sebastian Bach.</p>
<p>La musique "Tetris Type A (Hard Dance - JumpStyle Remix)" de TheFlasher7 viens de <a href="https://www.youtube.com/watch?v=mabhaNDNLvM">cette vidéo Youtube</a>. (musique non présente dans les archives au dessus)</p>
<?php
include_once('include/_foot.php');

?>

<?php
$titre_page = 'Scores';

include_once('include/_head.php');

include_once('include/id_bdd.php');




try {
	$bdd_connexion = new PDO('mysql:host='.$bdd_host.';port='.$bdd_port.';dbname='.$bdd_db, $bdd_user, $bdd_pass);
} catch(Exception $e) {
    exit('Erreur base de données '.$e->getCode().' : '.$e->getMessage()."\n");
}



$resultats=$bdd_connexion->query("SELECT COUNT(*) as nbchecked FROM tetris_scores WHERE checked = 1");
$resultats->setFetchMode(PDO::FETCH_OBJ);
if(!($ligne = $resultats->fetch()))
	exit('Erreur dans la base de données : la table des scores n\'existe pas.');

$nb_result = $ligne->nbchecked;

echo '<p>Il y a '.$nb_result.' score'.(($nb_result>1)?'s':'').' à afficher</p>';






if ($nb_result > 0)
{
	include_once('include/function_time.php');
	if ($nb_result > 1000) {
		?><p>Affichage des 1000 meilleurs scores :</p><?php
	}
	$resultats=$bdd_connexion->query("SELECT player_name, score, time, lignes, nb_tetromino, date FROM tetris_scores WHERE checked = 1 ORDER BY score DESC, time ASC LIMIT 1000 OFFSET 0");
	$resultats->setFetchMode(PDO::FETCH_OBJ);
	
	?>
	<table id="scores">
		<tr>
			<th>#</th>
			<th>Nom&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</th>
			<th>Score</th>
			<th>Lignes</th>
			<th>Pièces</th>
			<th>Durée&nbsp;&nbsp;</th>
			<th>Date</th>
		</tr>
		<?php
			$i=1;
			while ($ligne = $resultats->fetch())
			{
				?>
				<tr>
					<td><?php echo $i; ?></td>
					<td><?php echo htmlentities($ligne->player_name); ?></td>
					<td><?php echo $ligne->score; ?></td>
					<td><?php echo $ligne->lignes; ?></td>
					<td><?php echo $ligne->nb_tetromino; ?></td>
					<td><?php echo time_duration($ligne->time); ?></td>
					<td><?php echo ($ligne->date !== null) ? date('d/m/Y', $ligne->date) : '-'; ?></td>
				</tr>
				<?php
				$i++;
			}
		?>
	</table>
	<?php
}
include_once('include/_foot.php');

?>
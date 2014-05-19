<?php
include_once('include/id_bdd.php');

$bdd_querry_prepare = 'INSERT INTO '.$bdd_table.' VALUES ( null, :name , :score , :time , :lines , :nbtetro , :data , false);';

$min_score_to_saving = 1;





if (empty($_POST['data']))
	exit('error_empty');



// ceci est temporaire, cela permet de stocker
// les données pour effectuer des tests sur ce que le serveur reçoit comme données

$datas = base64_decode(strtr($_POST['data'], '-_', '+/'));

$output_data = Array();


$sizeof_init_data = ord($datas[0]);

if (strlen($datas) < $sizeof_init_data+1+5)
	exit('error_data_length : '.strlen($datas));
if ($sizeof_init_data != 48)
	exit('error_data_length : initial data length != 48 : '.$sizeof_init_data);
$init_data = substr($datas, 1, $sizeof_init_data);

/*
Structures des données initiales :
30 octets (char) : nom
4 octets (uint32 BE) : points
4 octets (uint32 BE) : lignes détruites
4 octets (uint32 BE) : tetrominos
4 octets (uint32 BE) : durée
*/
$output_data['player_name'] = substr($init_data, 0, 30);
$i=0;
for ($i=0; $i<strlen($output_data['player_name']); $i++)
	if ($output_data['player_name'][$i] == chr(0))
		break;
$output_data['player_name'] = substr($output_data['player_name'], 0, $i);

$init_data_tab = unpack('Nscore/NdelLines/Ntetrominoes/Ntime', substr($init_data, 32, 16));

$output_data['score'] = $init_data_tab['score'];
$output_data['delLines'] = $init_data_tab['delLines'];
$output_data['tetrominoes'] = $init_data_tab['tetrominoes'];
$output_data['time'] = $init_data_tab['time'];
$output_data['history'] = Array();


$datas = substr($datas, $sizeof_init_data+1);

$nbLineDatas = unpack('NnbVal/ClineSize', substr($datas, 0, 5));
$sizeof_data_row = $nbLineDatas['lineSize'] . "\n";
$nbLineDatas = $nbLineDatas['nbVal'] . "\n";

if ($nbLineDatas != $output_data['tetrominoes'])
	exit('error_data : number of data rows != dropped tetrominoes number');


$datas = substr($datas, 5);

if (strlen($datas) != $sizeof_data_row * $nbLineDatas)
	exit('error_data_length : data checkup part size expected ' . ($sizeof_data_row * $nbLineDatas) . ' but ' . strlen($datas) . ' B');

$datasRows = Array();
for ($i=0; $i<$nbLineDatas; ++$i)
{
	$datasRows[$i] = substr($datas, (int) ($i*$sizeof_data_row), (int) $sizeof_data_row);
}


// vérifie l'utilité de sauvegarder ce score
if ($output_data['score'] < $min_score_to_saving)
	exit('cancelled_score_to_low : score < '.$min_score_to_saving);



foreach ($datasRows as $row => $line)
{
	$output_data['history'][$row] = unpack('Nscore/NscoreDiff/NnbTetromino/NtimeMilliseconds/NnbDelLines/NnbDeLinesDiff/NnbManualDown/CtetroTO/ctetroX/ctetroY', $line);
	$output_data['history'][$row]['tetroType'] = ($output_data['history'][$row]['tetroTO']) >> 4;
	$output_data['history'][$row]['tetroOrientation'] = ($output_data['history'][$row]['tetroTO']) & 0xF;
	unset($output_data['history'][$row]['tetroTO']);
	// print_r($output_data['history'][$row]);
}


try {
	$bdd_connexion = new PDO('mysql:host='.$bdd_host.';port='.$bdd_port.';dbname='.$bdd_db, $bdd_user, $bdd_pass);
} catch(Exception $e) {
    exit('error_db_connect : '.$e->getCode().' ; '.$e->getMessage()."\n");
}


$req=$bdd_connexion->prepare($bdd_querry_prepare);
$req->execute(Array(
	'name' => $output_data['player_name'],
	'score' => $output_data['score'],
	'time' => $output_data['time'],
	'lines' => $output_data['delLines'],
	'nbtetro' => $output_data['tetrominoes'],
	'data' => serialize($output_data['history'])
));

	
exit('ok');
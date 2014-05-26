<?php


// $output_data



$matrix = Array();
for ($i=0; $i<10; $i++)
	for ($j=0; $j<22; $j++)
	{
		$matrix[$i][$j] = false;
	}


$checking_score = 0;
$checking_line = 0;
$checking_tetromino = 0;
$checking_timeMS = 0;

$data_valid = true;

foreach($output_data['history'] as $row => $data)
{
	// vérification des valeurs stoqués dans les données
	$checking_score+=$data['scoreDiff'];
	if ($checking_score != $data['score'])
	{
		echo 'error_checking : row ' . $row . ' : score diff in data. sum = ' . $checking_score . ' and data = ' . $data['score'];
		$data_valid = false;
		break;
	}
	$checking_line+=$data['nbDeLinesDiff'];
	if ($checking_line != $data['nbDelLines'])
	{
		echo 'error_checking : row ' . $row . ' : nb of del lines diff in data. sum = ' . $checking_line . ' and data = ' . $data['nbDelLines'];
		$data_valid = false;
		break;
	}
	$checking_tetromino++;
	if ($checking_tetromino != $data['nbTetromino'])
	{
		echo 'error_checking : row ' . $row . ' : nb of tetromino diff in data. sum = ' . $checking_tetromino . ' and data = ' . $data['nbTetromino'];
		$data_valid = false;
		break;
	}
	// -------------------------------------------------
	
	
	
	
}


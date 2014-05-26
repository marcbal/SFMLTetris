<?php

$tetrominos = Array(
    Array( // O
        Array(
            Array(0, 0, 0, 0),
            Array(0, 1, 1, 0),
            Array(0, 1, 1, 0),
            Array(0, 0, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 1, 1, 0),
            Array(0, 1, 1, 0),
            Array(0, 0, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 1, 1, 0),
            Array(0, 1, 1, 0),
            Array(0, 0, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 1, 1, 0),
            Array(0, 1, 1, 0),
            Array(0, 0, 0, 0)
        )
    ),

    Array( // I
        Array(
            Array(0, 0, 0, 0),
            Array(1, 1, 1, 1),
            Array(0, 0, 0, 0),
            Array(0, 0, 0, 0)
        ),

        Array(
            Array(0, 1, 0, 0),
            Array(0, 1, 0, 0),
            Array(0, 1, 0, 0),
            Array(0, 1, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 0, 0, 0),
            Array(1, 1, 1, 1),
            Array(0, 0, 0, 0)
        ),

        Array(
            Array(0, 0, 1, 0),
            Array(0, 0, 1, 0),
            Array(0, 0, 1, 0),
            Array(0, 0, 1, 0)
        )


    ),

    Array( // S
        Array(
            Array(0, 0, 0, 0),
            Array(0, 1, 1, 0),
            Array(1, 1, 0, 0),
            Array(0, 0, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(1, 0, 0, 0),
            Array(1, 1, 0, 0),
            Array(0, 1, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 0, 0, 0),
            Array(0, 1, 1, 0),
            Array(1, 1, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 1, 0, 0),
            Array(0, 1, 1, 0),
            Array(0, 0, 1, 0)
        )
    ),

    Array( // Z
        Array(
            Array(0, 0, 0, 0),
            Array(1, 1, 0, 0),
            Array(0, 1, 1, 0),
            Array(0, 0, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 1, 0, 0),
            Array(1, 1, 0, 0),
            Array(1, 0, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 0, 0, 0),
            Array(1, 1, 0, 0),
            Array(0, 1, 1, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 0, 1, 0),
            Array(0, 1, 1, 0),
            Array(0, 1, 0, 0)
        )
    ),

    Array( // L
        Array(
            Array(0, 0, 0, 0),
            Array(0, 0, 1, 0),
            Array(1, 1, 1, 0),
            Array(0, 0, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(1, 1, 0, 0),
            Array(0, 1, 0, 0),
            Array(0, 1, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 0, 0, 0),
            Array(1, 1, 1, 0),
            Array(1, 0, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 1, 0, 0),
            Array(0, 1, 0, 0),
            Array(0, 1, 1, 0)
        )
    ),

    Array( // J
        Array(
            Array(0, 0, 0, 0),
            Array(1, 0, 0, 0),
            Array(1, 1, 1, 0),
            Array(0, 0, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 1, 0, 0),
            Array(0, 1, 0, 0),
            Array(1, 1, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 0, 0, 0),
            Array(1, 1, 1, 0),
            Array(0, 0, 1, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 1, 1, 0),
            Array(0, 1, 0, 0),
            Array(0, 1, 0, 0)
        )
    ),

    Array( // T
        Array(
            Array(0, 0, 0, 0),
            Array(0, 1, 0, 0),
            Array(1, 1, 1, 0),
            Array(0, 0, 0, 0)
        ),

        Array(

            Array(0, 0, 0, 0),
            Array(0, 1, 0, 0),
            Array(1, 1, 0, 0),
            Array(0, 1, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 0, 0, 0),
            Array(1, 1, 1, 0),
            Array(0, 1, 0, 0)
        ),

        Array(
            Array(0, 0, 0, 0),
            Array(0, 1, 0, 0),
            Array(0, 1, 1, 0),
            Array(0, 1, 0, 0)
        ),
    )
);





























// $output_data



$matrix = Array();
for ($i=0; $i<10; $i++)
	for ($j=0; $j<22; $j++)
		$matrix[$i][$j] = false;


$checking_score = 0;
$checking_line = 0;
$checking_tetromino = 0;
$checking_timeMS = 0;

$data_valid = true;

foreach($output_data['history'] as $row => $data)
{
	// vérification des valeurs stockés dans les données
	$checking_score+=$data['scoreDiff'];
	if ($checking_score != $data['score'])
	{
		echo 'error_checking : row ' . $row . ' : score diff in data. sum = ' . $checking_score . ' and data = ' . $data['score'] . "\n";
		$data_valid = false;
		break;
	}
	$checking_line+=$data['nbDeLinesDiff'];
	if ($checking_line != $data['nbDelLines'])
	{
		echo 'error_checking : row ' . $row . ' : nb of del lines diff in data. sum = ' . $checking_line . ' and data = ' . $data['nbDelLines'] . "\n";
		$data_valid = false;
		break;
	}
	$checking_tetromino++;
	if ($checking_tetromino != $data['nbTetromino'])
	{
		echo 'error_checking : row ' . $row . ' : nb of tetromino diff in data. sum = ' . $checking_tetromino . ' and data = ' . $data['nbTetromino'] . "\n";
		$data_valid = false;
		break;
	}
	// -------------------------------------------------
	
	
	// on positionne la pièce indiqué dans les données sur la matrice de vérification
	$matrice_piece = Array();
	for ($i=0; $i<4; $i++)
		for ($j=0; $j<4; $j++)
			$matrice_piece[$i][$j] = $tetrominos[$data['tetroType']][$data['tetroOrientation']][$j][$i];
	
	$piece_pos_x = $data['tetroX'];
	$piece_pos_y = $data['tetroY']+2;	// +2 car il y a 2 cases au dessus de la matrice, qu'on ne voit pas
	
	for ($i=0; $i<4; $i++)
		for ($j=0; $j<4; $j++)
			if ($matrice_piece[$i][$j] == 1 && isset($matrix[$piece_pos_x+$i][$piece_pos_y+$j]))
			{
				if ($matrix[$piece_pos_x+$i][$piece_pos_y+$j])
				{
					echo 'error_checking : row ' . $row . ' : matrix already filled at position (' . ($piece_pos_x+$i) . ';' . ($piece_pos_y+$j) . ')' . "\n";
					$data_valid = false;
					break;
				}
				else
					$matrix[$piece_pos_x+$i][$piece_pos_y+$j] = true;
			}
	// ------------------------------------------------------------------------------
	
	
	
	// affichage :
	
	/*for ($i=0; $i<10; $i++)
	{
		echo '[';
		for ($j=0; $j<22; $j++)
			echo ($matrix[$i][$j])?'#':' ';
		echo "]\n";
	} // */
	
	// on detruit les lignes complètes et on les comptent
	$nb_del_lines = 0;
	for ($i=0; $i<22; $i++)
	{
		$full = true;
		
		for ($j=0; $j<10; $j++)
			if(!$matrix[$j][$i])
				$full = false;
		
		if ($full)
		{
			$nb_del_lines++;
			for ($j=0; $j<10; $j++)
				$matrix[$j][$i] = false;
			
			for ($j=$i; $j>0; $j--)
				for ($k=0; $k<10; $k++)
				$matrix[$k][$j] = $matrix[$k][$j-1];
			
			for ($j=0; $j<10; $j++)
				$matrix[$j][0] = false;
			
		}
	}
	
	if ($nb_del_lines != $data['nbDeLinesDiff'])
	{
		echo 'error_checking : row ' . $row . ' : nb of new del lines diff in data. simulated = ' . $nb_del_lines . ' and data = ' . $data['nbDeLinesDiff'] . "\n";
		$data_valid = false;
		break;
	}
	// --------------------------------------------------
	
	
	
	
	
	
	
	if (!$data_valid)
		break;
}


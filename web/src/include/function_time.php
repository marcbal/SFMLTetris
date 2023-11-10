<?php


	
// fonction récupéré d'un autre projet (marc)
function time_duration($time, $limit = 'd')
{
	$time = intval($time);
	if ($time < 60 OR $limit == 's')
		return $time.'s';
	if ($time < 3600 OR $limit == 'm')
		return floor($time/60).'m '.($time-60*floor($time/60)).'s';
	if ($time < 86400 OR $limit == 'h')
		return floor($time/3600).'h '. floor(($time-3600*floor($time/3600))/60).'m';
	else
		return floor($time/86400).'d '. floor(($time-86400*floor($time/86400))/3600).'h';
		
}
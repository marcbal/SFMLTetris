SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";

CREATE TABLE IF NOT EXISTS `tetris_scores` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `player_name` varchar(30) DEFAULT NULL,
  `score` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `lignes` int(11) NOT NULL,
  `nb_tetromino` int(11) NOT NULL,
  `check_data` longtext NOT NULL COMMENT 'serialised',
  `checked` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

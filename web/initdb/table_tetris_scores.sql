USE sfmltetris;

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";

CREATE TABLE IF NOT EXISTS `tetris_scores` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `player_name` varchar(30) DEFAULT NULL,
  `score` int NOT NULL,
  `time` int NOT NULL,
  `lignes` int NOT NULL,
  `nb_tetromino` int NOT NULL,
  `check_data` longtext NOT NULL COMMENT 'serialised',
  `checked` tinyint(1) NOT NULL DEFAULT '0',
  `date` bigint DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

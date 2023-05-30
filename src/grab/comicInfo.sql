CREATE TABLE `comic_info` (
	`id` BIGINT(20) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'comic id',
	`title` VARCHAR(256) NOT NULL COMMENT 'comic title' COLLATE 'utf8mb3_general_ci',
	`title_pinyin` VARCHAR(256) NOT NULL COMMENT 'pinyin of title' COLLATE 'utf8mb3_general_ci',
	`author` VARCHAR(64) NULL DEFAULT NULL COMMENT 'comic author' COLLATE 'utf8mb3_general_ci',
	`status` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' COMMENT '0-连载,1-完结,2-失效',
	`external_update_datetime` DATETIME NULL DEFAULT NULL,
	`description` VARCHAR(512) NULL DEFAULT NULL COLLATE 'utf8mb3_general_ci',
	`update_tm` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
	`type` CHAR(10) NOT NULL DEFAULT 'comic' COMMENT 'comic or novel' COLLATE 'utf8mb3_general_ci',
	`thumbnail_path` VARCHAR(100) NULL DEFAULT NULL COMMENT 'thumbnal content path 120*160' COLLATE 'utf8mb3_general_ci',
	`cover_path` VARCHAR(100) NULL DEFAULT NULL COMMENT 'cover path' COLLATE 'utf8mb3_general_ci',
	PRIMARY KEY (`id`) USING BTREE,
	INDEX `title` (`title`) USING BTREE,
	INDEX `title_pinyin` (`title_pinyin`) USING BTREE,
	INDEX `author` (`author`) USING BTREE
)
COLLATE='utf8mb3_general_ci'
ENGINE=InnoDB
AUTO_INCREMENT=9
;

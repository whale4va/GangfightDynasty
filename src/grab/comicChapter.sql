CREATE TABLE `comic_chapter` (
	`chapter_id` BIGINT(20) UNSIGNED NOT NULL AUTO_INCREMENT,
	`comic_id` BIGINT(20) UNSIGNED NOT NULL,
	`chapter_index` INT(10) UNSIGNED NOT NULL COMMENT 'th of the chapter',
	`chapter_name` VARCHAR(64) NULL DEFAULT NULL COLLATE 'utf8mb3_general_ci',
	`page_number` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'how many pages in the chapter,0 for novel',
	`type` CHAR(10) NOT NULL DEFAULT 'comic' COMMENT 'comic or novel' COLLATE 'utf8mb3_general_ci',
	`storage_type` CHAR(10) NOT NULL DEFAULT 'external' COMMENT 'external or local' COLLATE 'utf8mb3_general_ci',
	`local_url` VARCHAR(200) NULL DEFAULT NULL COMMENT 'local url of local storage' COLLATE 'utf8mb3_general_ci',
	`directories` TEXT NULL DEFAULT NULL COMMENT 'directories of files, sperated by chr(1)' COLLATE 'utf8mb3_general_ci',
	`files` TEXT NULL DEFAULT NULL COMMENT 'file names of every page, seperated by dir^Bname^A' COLLATE 'utf8mb3_general_ci',
	`update_tm` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
	PRIMARY KEY (`chapter_id`) USING BTREE,
	INDEX `comic_id` (`comic_id`) USING BTREE
)
COLLATE='utf8mb3_general_ci'
ENGINE=InnoDB
AUTO_INCREMENT=905
;

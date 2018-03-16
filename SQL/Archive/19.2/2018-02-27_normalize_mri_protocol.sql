-- This patch adds min & max columns for every field in `mri_protocol` which presently can hold range values. 
ALTER TABLE
	`mri_protocol`
		ADD COLUMN `TR_min` DECIMAL(7,4) DEFAULT NULL,
		ADD COLUMN `TR_max` DECIMAL(7,4) DEFAULT NULL,
		ADD COLUMN `TE_min` DECIMAL(7,4) DEFAULT NULL,
		ADD COLUMN `TE_max` DECIMAL(7,4)  DEFAULT NULL,
		ADD COLUMN `TI_min` DECIMAL(7,4)  DEFAULT NULL,
		ADD COLUMN `TI_max` DECIMAL(7,4)  DEFAULT NULL,
		ADD COLUMN `slice_thickness_min` DECIMAL(7,4) DEFAULT NULL,
		ADD COLUMN `slice_thickness_max` DECIMAL(7,4) DEFAULT NULL,
		ADD COLUMN `xspace_min` int(4) DEFAULT NULL,
		ADD COLUMN `xspace_max` int(4) DEFAULT NULL,
		ADD COLUMN `yspace_min` int(4) DEFAULT NULL,
		ADD COLUMN `yspace_max` int(4) DEFAULT NULL,
		ADD COLUMN `zspace_min` int(4) DEFAULT NULL,
		ADD COLUMN `zspace_max` int(4) DEFAULT NULL,
		ADD COLUMN `xstep_min` varchar(5) DEFAULT NULL,
		ADD COLUMN `xstep_max` varchar(5) DEFAULT NULL,
    ADD COLUMN `ystep_min` varchar(5) DEFAULT NULL,
    ADD COLUMN `ystep_max` varchar(5) DEFAULT NULL,
    ADD COLUMN `zstep_min` varchar(5) DEFAULT NULL,
    ADD COLUMN `zstep_max` varchar(5) DEFAULT NULL,
		ADD COLUMN `time_min` int(4) DEFAULT NULL AFTER `series_description_regex`,
		ADD COLUMN `time_max` int(4) DEFAULT NULL AFTER `series_description_regex`,
		DROP `FOV_x`,
		DROP `FOV_y`,
		DROP `FOV_z`;

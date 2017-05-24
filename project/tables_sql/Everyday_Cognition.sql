CREATE TABLE `Everyday_Cognition` (
`CommentID` varchar(255) NOT NULL default '',

                            `UserID` varchar(255) default NULL,

                            `Examiner` varchar(255) default NULL,

                            `Testdate` timestamp DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,

                            `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Candidate_Age` varchar(255) default NULL,
`Window_Difference` varchar(255) default NULL,
`memory` varchar(255) default NULL,
`language` varchar(255) default NULL,
`visual_spatial_perceptual` varchar(255) default NULL,
`ef_planning` varchar(255) default NULL,
`ef_organization` varchar(255) default NULL,
`ef_attention` varchar(255) default NULL,
`total_score` varchar(255) default NULL,
`memory_0` enum('1','2','3','4','5') default NULL,
`memory_1` enum('1','2','3','4','5') default NULL,
`memory_2` enum('1','2','3','4','5') default NULL,
`memory_3` enum('1','2','3','4','5') default NULL,
`memory_4` enum('1','2','3','4','5') default NULL,
`memory_5` enum('1','2','3','4','5') default NULL,
`memory_6` enum('1','2','3','4','5') default NULL,
`memory_7` enum('1','2','3','4','5') default NULL,
`language_0` enum('1','2','3','4','5') default NULL,
`language_1` enum('1','2','3','4','5') default NULL,
`language_2` enum('1','2','3','4','5') default NULL,
`language_3` enum('1','2','3','4','5') default NULL,
`language_4` enum('1','2','3','4','5') default NULL,
`language_5` enum('1','2','3','4','5') default NULL,
`language_6` enum('1','2','3','4','5') default NULL,
`language_7` enum('1','2','3','4','5') default NULL,
`language_8` enum('1','2','3','4','5') default NULL,
`visual_spatial_perceptual_0` enum('1','2','3','4','5') default NULL,
`visual_spatial_perceptual_1` enum('1','2','3','4','5') default NULL,
`visual_spatial_perceptual_2` enum('1','2','3','4','5') default NULL,
`visual_spatial_perceptual_3` enum('1','2','3','4','5') default NULL,
`visual_spatial_perceptual_4` enum('1','2','3','4','5') default NULL,
`visual_spatial_perceptual_5` enum('1','2','3','4','5') default NULL,
`visual_spatial_perceptual_6` enum('1','2','3','4','5') default NULL,
`ef_planning_0` enum('1','2','3','4','5') default NULL,
`ef_planning_1` enum('1','2','3','4','5') default NULL,
`ef_planning_2` enum('1','2','3','4','5') default NULL,
`ef_planning_3` enum('1','2','3','4','5') default NULL,
`ef_planning_4` enum('1','2','3','4','5') default NULL,
`ef_organization_0` enum('1','2','3','4','5') default NULL,
`ef_organization_1` enum('1','2','3','4','5') default NULL,
`ef_organization_2` enum('1','2','3','4','5') default NULL,
`ef_organization_3` enum('1','2','3','4','5') default NULL,
`ef_organization_4` enum('1','2','3','4','5') default NULL,
`ef_organization_5` enum('1','2','3','4','5') default NULL,
`ef_attention_0` enum('1','2','3','4','5') default NULL,
`ef_attention_1` enum('1','2','3','4','5') default NULL,
`ef_attention_2` enum('1','2','3','4','5') default NULL,
`ef_attention_3` enum('1','2','3','4','5') default NULL,
PRIMARY KEY  (`CommentID`)

              );

CREATE TABLE `Clinical_Family_History` (
`CommentID` varchar(255) NOT NULL default '',

                            `UserID` varchar(255) default NULL,

                            `Examiner` varchar(255) default NULL,

                            `Testdate` timestamp DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,

                            `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Candidate_Age` varchar(255) default NULL,
`Window_Difference` varchar(255) default NULL,
`family_history_ad` enum('yes','no','unknown') default NULL,
`ad_sibling_yes_or_no` enum('yes','no') default NULL,
`ad_sibling_amount` varchar(255) default NULL,
`ad_sibling_age_onset` varchar(255) default NULL,
`ad_AD mother_yes_no_unknown` enum('yes','no','unknown') default NULL,
`ad_AD mother_age_of_onset` varchar(255) default NULL,
`ad_AD father_yes_no_unknown` enum('yes','no','unknown') default NULL,
`ad_AD father_age_of_onset` varchar(255) default NULL,
`family_history_nd` enum('yes','no','unknown') default NULL,
`nd_sibling_yes_or_no` enum('yes','no') default NULL,
`nd_sibling_amount` varchar(255) default NULL,
`nd_sibling_age_onset` varchar(255) default NULL,
`nd_ND mother_yes_no_unknown` enum('yes','no','unknown') default NULL,
`nd_ND mother_age_of_onset` varchar(255) default NULL,
`nd_ND father_yes_no_unknown` enum('yes','no','unknown') default NULL,
`nd_ND father_age_of_onset` varchar(255) default NULL,
PRIMARY KEY  (`CommentID`)

              );

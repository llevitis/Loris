CREATE TABLE `Functional_Activity` (
`CommentID` varchar(255) NOT NULL default '',

                            `UserID` varchar(255) default NULL,

                            `Examiner` varchar(255) default NULL,

                            `Testdate` timestamp DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,

                            `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Candidate_Age` varchar(255) default NULL,
`Window_Difference` varchar(255) default NULL,
`total_score` varchar(255) default NULL,
`functional_activity_0` enum('0','1','2','3') default NULL,
`functional_activity_1` enum('0','1','2','3') default NULL,
`functional_activity_2` enum('0','1','2','3') default NULL,
`functional_activity_3` enum('0','1','2','3') default NULL,
`functional_activity_4` enum('0','1','2','3') default NULL,
`functional_activity_5` enum('0','1','2','3') default NULL,
`functional_activity_6` enum('0','1','2','3') default NULL,
`functional_activity_7` enum('0','1','2','3') default NULL,
`functional_activity_8` enum('0','1','2','3') default NULL,
`functional_activity_9` enum('0','1','2','3') default NULL,
PRIMARY KEY  (`CommentID`)

              );

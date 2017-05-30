CREATE TABLE `Screening_General_Inclusion_Criteria` (
`CommentID` varchar(255) NOT NULL default '',

                            `UserID` varchar(255) default NULL,

                            `Examiner` varchar(255) default NULL,

                            `Testdate` timestamp DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,

                            `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Candidate_Age` varchar(255) default NULL,
`Window_Difference` varchar(255) default NULL,
`inclusion_criteria_0_yes_or_no` enum('no','yes') default NULL,
`inclusion_criteria_1_yes_or_no` enum('no','yes') default NULL,
`inclusion_criteria_2_yes_or_no` enum('no','yes') default NULL,
`inclusion_criteria_3_yes_or_no` enum('no','yes') default NULL,
`inclusion_criteria_4_yes_or_no` enum('no','yes') default NULL,
`inclusion_criteria_5_yes_or_no` enum('no','yes') default NULL,
`inclusion_criteria_6_yes_or_no` enum('no','yes') default NULL,
`inclusion_criteria_7_yes_or_no` enum('no','yes') default NULL,
`inclusion_criteria_8_yes_or_no` enum('no','yes') default NULL,
`inclusion_criteria_9_yes_or_no` enum('no','yes') default NULL,
`inclusion_criteria_10_yes_or_no` enum('no','yes') default NULL,
PRIMARY KEY  (`CommentID`)

              );

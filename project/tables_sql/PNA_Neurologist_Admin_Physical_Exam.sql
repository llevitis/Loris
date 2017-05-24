CREATE TABLE `PNA_Neurologist_Admin_Physical_Exam` (
`CommentID` varchar(255) NOT NULL default '',

                            `UserID` varchar(255) default NULL,

                            `Examiner` varchar(255) default NULL,

                            `Testdate` timestamp DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,

                            `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Candidate_Age` varchar(255) default NULL,
`Window_Difference` varchar(255) default NULL,
`physical_examination_0_abnormal_or_normal` enum('no','yes') default NULL,
`physical_examination_0_comment` varchar(255) default NULL,
`physical_examination_1_abnormal_or_normal` enum('no','yes') default NULL,
`physical_examination_1_comment` varchar(255) default NULL,
`physical_examination_2_abnormal_or_normal` enum('no','yes') default NULL,
`physical_examination_2_comment` varchar(255) default NULL,
`physical_examination_3_abnormal_or_normal` enum('no','yes') default NULL,
`physical_examination_3_comment` varchar(255) default NULL,
`physical_examination_4_abnormal_or_normal` enum('no','yes') default NULL,
`physical_examination_4_comment` varchar(255) default NULL,
`physical_examination_5_abnormal_or_normal` enum('no','yes') default NULL,
`physical_examination_5_comment` varchar(255) default NULL,
`physical_examination_6_abnormal_or_normal` enum('no','yes') default NULL,
`physical_examination_6_comment` varchar(255) default NULL,
`physical_examination_7_abnormal_or_normal` enum('no','yes') default NULL,
`physical_examination_7_comment` varchar(255) default NULL,
`physical_examination_8_abnormal_or_normal` enum('no','yes') default NULL,
`physical_examination_8_comment` varchar(255) default NULL,
`physical_examination_9_abnormal_or_normal` enum('no','yes') default NULL,
`physical_examination_9_comment` varchar(255) default NULL,
`4_rectal_exam` enum('no','yes') default NULL,
`5_genital_exam` enum('no','yes') default NULL,
`6_conditions` enum('no','yes') default NULL,
PRIMARY KEY  (`CommentID`)

              );

CREATE TABLE `Screening_Summary_Diagnosis_AD_Mixed` (
`CommentID` varchar(255) NOT NULL default '',

                            `UserID` varchar(255) default NULL,

                            `Examiner` varchar(255) default NULL,

                            `Testdate` timestamp DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,

                            `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Candidate_Age` varchar(255) default NULL,
`Window_Difference` varchar(255) default NULL,
`q1_yes_no` enum('yes','no') default NULL,
`q1_no_comment` varchar(255) default NULL,
`q1_no_comment_status` enum('not_answered') default NULL,
`q2_diagnosis` enum('no_previous_neurological_diagnosis') default NULL,
`q3_materials` enum('screening_test_battery','clinical_chart','other') default NULL,
`q3_other` varchar(255) default NULL,
`q3_other_status` enum('not_answered') default NULL,
`q4` varchar(255) default NULL,
`q4_status` enum('not_answered') default NULL,
`diagnostic_evaluator` enum('physician','research_nurse','research_coordinator','research_assistant') default NULL,
`diagnostic_evaluator_name` varchar(255) default NULL,
`diagnostic_evaluator_name_status` enum('not_answered') default NULL,
`diagnostic_evaluation_date` date default NULL,
PRIMARY KEY  (`CommentID`)

              );

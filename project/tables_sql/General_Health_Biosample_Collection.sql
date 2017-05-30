CREATE TABLE `General_Health_Biosample_Collection` (
`CommentID` varchar(255) NOT NULL default '',

                            `UserID` varchar(255) default NULL,

                            `Examiner` varchar(255) default NULL,

                            `Testdate` timestamp DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,

                            `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Candidate_Age` varchar(255) default NULL,
`Window_Difference` varchar(255) default NULL,
`blood_sample_date` date default NULL,
`blood_sample_time_of_collection` varchar(255) default NULL,
`blood_sample_fasting_yes_no` enum('yes','no') default NULL,
`blood_sample_time_of_last_meal` varchar(255) default NULL,
`blood_sample_fasting_period` varchar(255) default NULL,
`buccal_sample_date` date default NULL,
`buccal_sample_time_of_collection` varchar(255) default NULL,
`urine_sample_date` date default NULL,
`urine_sample_time_of_collection` varchar(255) default NULL,
`hair_sample_date` date default NULL,
`hair_sample_time_of_collection` varchar(255) default NULL,
`saliva_sample_date` date default NULL,
`saliva_sample_time_of_collection` varchar(255) default NULL,
`saliva_sample_time_elapsed_since_last_meal` varchar(255) default NULL,
`saliva_sample_time_elapsed_unit` enum('min','hours') default NULL,
`fecal_sample_date` date default NULL,
`fecal_sample_time_of_collection` varchar(255) default NULL,
`fecal_sample_time_elapsed_since_collection` varchar(255) default NULL,
`glucose` enum('normal','1+50mg/dl','2+100mg/dl','3+300mg/dl','4+1000mg/dl','not_done') default NULL,
`protein` enum('negative','1+30mg/dl','2+100mg/dl','3+500mg/dl','not_done') default NULL,
PRIMARY KEY  (`CommentID`)

              );

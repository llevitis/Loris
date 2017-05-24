CREATE TABLE `MAYONNAISE` (
`CommentID` varchar(255) NOT NULL default '',

                            `UserID` varchar(255) default NULL,

                            `Examiner` varchar(255) default NULL,

                            `Testdate` timestamp DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,

                            `Data_entry_completion_status` enum('Incomplete','Complete') NOT NULL default 'Incomplete',
`Date_taken` date default NULL,
`Candidate_Age` varchar(255) default NULL,
`Window_Difference` varchar(255) default NULL,
`Name` varchar(255) default NULL,
`Name_status` enum('not_answered') default NULL,
`Wizard` enum('Im_a_what','Oooohh_hell_yes','OK','Other') default NULL,
`Other` varchar(255) default NULL,
`Other_status` enum('not_answered') default NULL,
`Mayo` enum('yes','no','not_answered') default NULL,
`David` varchar(255) default NULL,
`Favourite` varchar(255) default NULL,
`Favourite_status` enum('not_answered') default NULL,
`Birthday_date` date default NULL,
`Birthday_date_status` enum('not_answered') default NULL,
`concussion_1_description` varchar(255) default NULL,
`concussion_1_hospitalized` varchar(255) default NULL,
`concussion_1_age` varchar(255) default NULL,
`concussion_2_description` varchar(255) default NULL,
`concussion_2_hospitalized` varchar(255) default NULL,
`concussion_2_age` varchar(255) default NULL,
`concussion_3_description` varchar(255) default NULL,
`concussion_3_hospitalized` varchar(255) default NULL,
`concussion_3_age` varchar(255) default NULL,
PRIMARY KEY  (`CommentID`)

              );

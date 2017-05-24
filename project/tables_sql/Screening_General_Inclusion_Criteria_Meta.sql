INSERT INTO test_names(Test_name, Full_name, Sub_Group) VALUES('Screening_General_Inclusion_Criteria', "General Inclusion Criteria",
(SELECT ID FROM test_subgroups WHERE Subgroup_name='Instruments'));
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('Screening_General_Inclusion_Criteria','Screening_General_Inclusion_Criteria_page1', "Page 1", 1);
INSERT INTO test_battery (Test_name, AgeMinDays,AgeMaxDays, Stage, SubprojectID, Visit_label)
VALUES('Screening_General_Inclusion_Criteria', 0,0, 'Visit', '1', 'V1');
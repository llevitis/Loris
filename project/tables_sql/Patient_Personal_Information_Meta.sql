INSERT INTO test_names(Test_name, Full_name, Sub_Group) VALUES('Patient_Personal_Information', "Patient Personal Information",
(SELECT ID FROM test_subgroups WHERE Subgroup_name='Instruments'));
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('Patient_Personal_Information','Patient_Personal_Information_page1', "Page 1", 1);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('Patient_Personal_Information','Patient_Personal_Information_page2', "Page 2", 2);
INSERT INTO test_battery (Test_name, AgeMinDays,AgeMaxDays, Stage, SubprojectID, Visit_label)
VALUES('Patient_Personal_Information', 0,0, 'Visit', '1', 'V1');
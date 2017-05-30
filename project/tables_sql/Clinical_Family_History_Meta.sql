INSERT INTO test_names(Test_name, Full_name, Sub_Group) VALUES('Clinical_Family_History', "Family History",
(SELECT ID FROM test_subgroups WHERE Subgroup_name='Instruments'));
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('Clinical_Family_History','Clinical_Family_History_page1', "Page 1", 1);
INSERT INTO test_battery (Test_name, AgeMinDays,AgeMaxDays, Stage, SubprojectID, Visit_label)
VALUES('Clinical_Family_History', 0,0, 'Visit', '1', 'V1');
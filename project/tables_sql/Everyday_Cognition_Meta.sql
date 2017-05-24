INSERT INTO test_names(Test_name, Full_name, Sub_Group) VALUES('Everyday_Cognition', "Everyday Cognition",
(SELECT ID FROM test_subgroups WHERE Subgroup_name='Instruments'));
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('Everyday_Cognition','Everyday_Cognition_page1', "Page 1", 1);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('Everyday_Cognition','Everyday_Cognition_page2', "Page 2", 2);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('Everyday_Cognition','Everyday_Cognition_page3', "Page 3", 3);
INSERT INTO test_battery (Test_name, AgeMinDays,AgeMaxDays, Stage, SubprojectID, Visit_label)
VALUES('Everyday_Cognition', 0,0, 'Visit', '1', 'V1');
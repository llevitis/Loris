INSERT INTO test_names(Test_name, Full_name, Sub_Group) VALUES('Functional_Activity', "Functional Activity",
(SELECT ID FROM test_subgroups WHERE Subgroup_name='Instruments'));
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('Functional_Activity','Functional_Activity_page1', "Page 1", 1);
INSERT INTO test_battery (Test_name, AgeMinDays,AgeMaxDays, Stage, SubprojectID, Visit_label)
VALUES('Functional_Activity', 0,0, 'Visit', '1', 'V1');
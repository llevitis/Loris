INSERT INTO test_names(Test_name, Full_name, Sub_Group)
VALUES('MAYONNAISE', "MAYONNAISE On Front End", (SELECT
ID FROM test_subgroups WHERE Subgroup_name='Instruments'));
INSERT INTO instrument_subtests (Test_name, Subtest_name,
Description, Order_number) VALUES ('MAYONNAISE',
'MAYONNAISE_page1', "Page 1", 1);
INSERT INTO test_battery (Test_name, AgeMinDays,
AgeMaxDays, Stage, SubprojectID, Visit_label)
VALUES('MAYONNAISE', 0,0, 'Visit', '2', 'V1');

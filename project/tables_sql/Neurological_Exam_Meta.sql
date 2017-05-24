INSERT INTO test_names(Test_name, Full_name, Sub_Group) VALUES('Neurological_Exam', "Neurological Exam",
(SELECT ID FROM test_subgroups WHERE Subgroup_name='Instruments'));
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('Neurological_Exam','Neurological_Exam_page1', "Page 1", 1);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('Neurological_Exam','Neurological_Exam_page2', "Page 2", 2);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('Neurological_Exam','Neurological_Exam_page3', "Page 3", 3);
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('Neurological_Exam','Neurological_Exam_page4', "Page 4", 4);
INSERT INTO test_battery (Test_name, AgeMinDays,AgeMaxDays, Stage, SubprojectID, Visit_label)
VALUES('Neurological_Exam', 0,0, 'Visit', '1', 'V1');
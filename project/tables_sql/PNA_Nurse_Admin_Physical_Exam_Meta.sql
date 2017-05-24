INSERT INTO test_names(Test_name, Full_name, Sub_Group) VALUES('PNA_Nurse_Admin_Physical_Exam', "Physical and Neurological Assessment: Nurse Administered Physical Exam",
(SELECT ID FROM test_subgroups WHERE Subgroup_name='Instruments'));
INSERT INTO instrument_subtests (Test_name, Subtest_name, Description, Order_number) VALUES ('PNA_Nurse_Admin_Physical_Exam','PNA_Nurse_Admin_Physical_Exam_page1', "Page 1", 1);
INSERT INTO test_battery (Test_name, AgeMinDays,AgeMaxDays, Stage, SubprojectID, Visit_label)
VALUES('PNA_Nurse_Admin_Physical_Exam', 0,0, 'Visit', '1', 'V1');
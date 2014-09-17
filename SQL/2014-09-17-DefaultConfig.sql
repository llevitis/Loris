-- default dicom_archive settings

-- patientIDRegex
INSERT INTO Config (ConfigID, Value) VALUES ("/./");

-- patientNameRegex
INSERT INTO Config (ConfigID, Value) VALUES ("/./i");

-- LegoPhantomRegex
INSERT INTO Config (ConfigID, Value) VALUES ("/./i");

-- LivingPhantomRegex
INSERT INTO Config (ConfigID, Value) VALUES ("/./i");

-- showTransferStatus
INSERT INTO Config (ConfigID, Value) VALUES ("false");


-- default dashboard settings

INSERT INTO Config (ConfigID, Value) VALUES ("This database provides an on-line mechanism to store both MRI and behavioral data collected from various locations. Within this framework, there are several tools that will make this process as efficient and simple as possible. For more detailed information regarding any aspect of the database, please click on the Help icon at the top right. Otherwise, feel free to contact us at the DCC. We strive to make data collection almost fun.");

-- default mail settings

-- From
INSERT INTO Config (ConfigID, Value) VALUES ("nobody@example.com");

-- Reply-to
INSERT INTO Config (ConfigID, Value) VALUES ("nobody@example.com");

-- X-MimeOLE
INSERT INTO Config (ConfigID, Value) VALUES ("Produced by LorisDB");

-- default www settings

-- host
INSERT INTO Config (ConfigID, Value) VALUES ("localhost");

-- url
INSERT INTO Config (ConfigID, Value) VALUES ("Produced by LorisDB");

-- default study variables

-- additional_user_info
INSERT INTO Config (ConfigID, Value) VALUES (1);

-- title
INSERT INTO Config (ConfigID, Value) VALUES ("Example Study");

-- studylogo
INSERT INTO Config (ConfigID, Value) VALUES ("images/neuro_logo_blue.gif");

-- columnThreshold
INSERT INTO Config (ConfigID, Value) VALUES (250);

-- useEDC
INSERT INTO Config (ConfigID, Value) VALUES ("false");

-- ageMin
INSERT INTO Config (ConfigID, Value) VALUES (8);

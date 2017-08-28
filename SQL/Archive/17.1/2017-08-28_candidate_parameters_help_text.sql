UPDATE help
  SET content = 'The Candidate Parameters module allows users to add or edit general information about the candidate, as well as key fields such as consent and study participation status.  Candidate information stored in this module should not change over time, or be specific to any given timepoint.\r\n\r\nThis module is organized into three tabs, visible to authorized users: "Candidate Information", "Participant Status", and "Consent Status". To return to the Candidate Profile page showing the list of timepoints, please click the "Return to timepoint list" button.\r\n\r\n<b>Candidate Information</b>\r\nThe Candidate Information tab allows users to document any additional comments about the candidate that may be important for analysis, as well as external identifiers. Please note the Caveat Emptor Flag is set to "False" by default. A candidate with a unique case for data analysis should have the Caveat Emptor Flag marked as "True". Select the reason for this caveat flag via the drop-down option(s) listing common caveat categories for the study. If “Other” is selected, specify the reason in the accompanying textbox below. To save any updated information, users must click “Update”.\r\n\r\n<b>Participant Status</b>\r\nIf the status of a candidate within a study changes, the participant status for that candidate can be updated to one of the following options: Active, Refused/Not Enrolled, Ineligible, Excluded, Inactive, Incomplete, or Complete.\r\n• <i>Active:</i> Candidate is active in the study\r\n• <i>Refused/Not Enrolled:</i> Candidate was recruited for the study but opted out\r\n• <i>Ineligible:</i> Candidate met exclusionary criterion/criteria during screening and was never scheduled for a visit\r\n• <i>Excluded:</i> Candidate was enrolled but met exclusionary criterion/criteria after starting the study (e.g. scan was reviewed as exclusionary by radiologist)\r\n• <i>Inactive:</i> Candidate continues to be part of the study but currently is inactive (e.g. Candidate is "Unsure" about continuing, "Requiring further investigation", or "Not responding")\r\n• <i>Incomplete:</i> Candidate has withdrawn.\r\n• <i>Complete:</i> Candidate has completed the study.\r\n\r\nIf a candidate is updated to <i>Inactive</i> or <i>Incomplete</i> status, enter the reason (required) from the drop-down menu options and/or providing comments in the “Comments” section.  Click “Update” to save this change.\r\n\r\n<b>Consent Status</b>\r\nThis tab stores a candidate’s consent status;  note that written consent is required prior to registering any given candidate in LORIS.\r\n• <i>Consent to Study:</i> Select "Yes” or “No", based on whether written consent was obtained for participation in the study\r\n• <i>Date of Consent to Study:</i> This field is required if Consent to Study is set to “Yes”.\r\n• <i>Date of Withdrawal of Consent to Study:</i> To be completed if a candidate withdraws their consent to participate in the study at any time.\r\nFor all consent date fields, the date value must be entered twice for confirmation, to minimize data entry error.\r\nMany studies require additional types of consent for specific procedures (i.e. consent to draw blood) or subprojects. Similar consent fields may appear for these additional consent items pertaining.', created = '2017-08-28 00:00:00'
WHERE topic = 'Candidate Parameters';

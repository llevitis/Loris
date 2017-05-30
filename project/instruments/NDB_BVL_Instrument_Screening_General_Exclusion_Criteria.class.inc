<?php
/*
 * This file contains the NDB_BVL_Instrument_Neurological_Exam
 * class
 *
 * PHP Version 5
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */

/**
 * Creates the form elements for the Screening General Exclusion Criteria instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */

class NDB_BVL_Instrument_Screening_General_Exclusion_Criteria extends NDB_BVL_Instrument
{
    var $ValidityEnabled  = false;
    var $ValidityRequired = false;

    /**
     * Sets up basic data, such as the LorisForm object, and so on.
     *
     * @param string $commentID the CommentID identifying the data to load
     * @param string $page      if a multipage form, the page to show
     *
     * @return void
     * @access public
     */
    function setup($commentID, $page)
    {
        $this->formType = "XIN";
        $this->form     = new LorisForm('Screening_General_Exclusion_Criteria_form');
        $this->page     = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = 'Screening_General_Exclusion_Criteria';           // test_names.Test_name
        $this->table    = 'Screening_General_Exclusion_Criteria';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields = array("Date_taken");

        //The array of selects with multiple answers allowed
        //Any HTML_Quickform multiple selects must be listed here
        $this->_selectMultipleElements = array();

        // required fields for data entry completion status
        $this->_requiredElements = array(
                                    'Examiner',
                                    'CommentID',
                                   );

        $config            = NDB_Config::singleton();
        $this->dateOptions = array(
                              'language'         => 'en',
                              'format'           => 'YMd',
                              'minYear'          => $config->getSetting('startYear'),
                              'maxYear'          => $config->getSetting('endYear'),
                              'addEmptyOption'   => true,
                              'emptyOptionValue' => null,
                             );

        // setup the form
        $this->_setupForm();

    }

    //If the instrument is not paged, remove the switch from the _setupForm method and add all the form Elements in this function.

    /**
     * Method to build the LorisForm object into a paged form
     *
     * @return void
     * @access private
     */
    function _setupForm()
    {
        //determine page to display
        if (preg_match(
            "/Screening_General_Exclusion_Criteria(_page[0-9]+)/",
            $this->page,
            $matches
        )) {
            call_user_func(array($this, $matches[1]));
        } else {
            $this->_main();
        }
        $this->form->addFormRule(array(&$this, 'XINValidate'));
    }

    /**
     * generates the main page of the form.
     *
     * @return void
     * @access private
     */
    function _main()
    {
        // display test name
        $this->addHeader("General Exclusion Criteria");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

    }

    function _page1()
    {

        $this->addHeader("General Exclusion Criteria");

        $yesNoOptions = array(
                         null  => "",
                         "no"  => "No",
                         "yes" => "Yes",
                        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            ""
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Yes/No"
        );
        $this->form->addGroup(
            $group,
            "exclusion_criteria_group_1_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        $exclusionCriteriaGroup1Names = array(
                                         "In treatment with any anti-inflammatory drugs, which cannot be 
            discontinued throughout the course of the study. (Ex. Aspirin at 
            doses higher than 325 mg/day).",
                                         "Residence in skilled nursing facility",
                                         "Within 4 weeks, had major surgery",
                                         "History of symptomatic stroke with hospitalization and history of 
            planned carotid revascularization (if enrolled with TIA)",
                                         "Cancer within 2 years or currently",
                                         "History of anaphylactic reaction",
                                         "Current abnormalities in B12. Low B12 is exclusionary, unless follow-up
            labs (homocysteine and methylmalonic acid) indicate physiological
            insignificance.",
                                         "History of schizophrenia (DSM IV criteria) within the past 1 year",
                                         "Psychotic, agitation or behavioural problems within the last 3 months, which 
            could lead to difficulty complying with the protocol",
                                         "Alcohol or any substance abuse or dependence within the past 2 years 
            (DSM IV).",
                                         "Dyslexia",
                                         "History of intracranial surgery",
                                         "Significant brain trauma",
                                        );

        for ($i = 0; $i < count($exclusionCriteriaGroup1Names); $i++) {
            $group[] =& $this->createLabel($exclusionCriteriaGroup1Names[$i]);
            $group[] =& $this->createSelect(
                "exclusion_criteria_group_1_" . $i . "_yes_or_no",
                "exclusion_criteria_group_1_yes_or_no",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "exclusion_criteria_group_1_" . $i . "_yes_or_no",
                array("exclusion_criteria_group_1_" . $i . "_yes_or_no{@}=={@}"),
                "Required.",
                "exclusion_criteria_group_1_" . $i
            );
            $this->addGroup(
                $group,
                "exclusion_criteria_group_1_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        /** Abnormality Disease **/

        $this->addLabel(
            "<h4>Abnormality/disease that is not controlled through a stable regimen
 in the areas of: </h4>"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            ""
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Yes/No"
        );
        $this->form->addGroup(
            $group,
            "abnormality_disease_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        $abnormalityDiseaseNames = array(
                                    "Endocrine",
                                    "Gastrointestinal",
                                    "Cardiovascular",
                                    "Hematological",
                                    "Hepatic",
                                    "Immunological (e.g. HIV)",
                                    "Renal",
                                    "Respiratory",
                                    "Genitourinary",
                                    "Major neurological disorder (e.g. diagnostic of epilepsy 
            in use of anti-elipetic drugs)",
                                   );

        for ($i = 0; $i < count($abnormalityDiseaseNames); $i++) {
            $group[] =& $this->createLabel($abnormalityDiseaseNames[$i]);
            $group[] =& $this->createSelect(
                "abnormality_disease_" . $i . "_yes_or_no",
                "abnormality_disease_yes_or_no",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "abnormality_disease_" . $i . "_yes_or_no",
                array("abnormality_disease_" . $i . "_yes_or_no{@}=={@}"),
                "Required.",
                "abnormality_disease_" . $i
            );
            $this->addGroup(
                $group,
                "abnormality_disease_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }
    }

    function _page2()
    {
        $this->addHeader("General Exclusion Criteria");

        $yesNoOptions = array(
                         null  => "",
                         "no"  => "No",
                         "yes" => "Yes",
                        );

        /** Contraindications to MRI **/

        $contraindicationsToMRINames = array(
                                        "Pacemaker",
                                        "Cardiac defibrillator",
                                        "Implanted material with electric or magnetic system",
                                        "Vascular clips",
                                        "Mechanical heart valve",
                                        "Cochlear implant",
                                        "Claustrophobia",
                                        "Transdermal patches (if not able to remove)",
                                       );

        $this->addLabel("");

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Contraindications to MRI:"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Yes/No"
        );
        $this->form->addGroup(
            $group,
            "contraindications_to_mri_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($contraindicationsToMRINames); $i++) {
            $group[] =& $this->createLabel($contraindicationsToMRINames[$i]);
            $group[] =& $this->createSelect(
                "contraindications_to_mri_" . $i . "_yes_or_no",
                "contraindications_to_mri_yes_or_no",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "contraindications_to_mri_" . $i . "_yes_or_no",
                array("contraindications_to_mri_" . $i . "_yes_or_no{@}=={@}"),
                "Required.",
                "contraindications_to_mri_" . $i
            );
            $this->addGroup(
                $group,
                "contraindications_to_mri_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        /** Contraindications to PET **/

        $contraindicationsToPETNames = array(
                                        "Participated in a PET research study or other study involving 
            administration of a radioactive substance or ionizing radiation within 
            12 months prior to screening",
                                        "Pregnancy or breast feeding",
                                       );

        $this->addLabel("");

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Contraindications to PET"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Yes/No"
        );
        $this->form->addGroup(
            $group,
            "contraindications_to_pet_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($contraindicationsToPETNames); $i++) {
            $group[] =& $this->createLabel($contraindicationsToPETNames[$i]);
            $group[] =& $this->createSelect(
                "contraindications_to_pet_" . $i . "_yes_or_no",
                "contraindications_to_pet_yes_or_no",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "contraindications_to_pet_" . $i . "_yes_or_no",
                array("contraindications_to_pet_" . $i . "_yes_or_no{@}=={@}"),
                "Required.",
                "contraindications_to_pet_" . $i
            );
            $this->addGroup(
                $group,
                "contraindications_to_pet_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        /** Contraindications to lumbar puncture **/

        $contraindicationsToLumbarPunctureNames = array(
                                                   "Current use of anticoagulation (e.g. warfarin)",
                                                   "Skin injection in the lumbar region",
                                                   "Coagulopathy",
                                                   "Recent lumbar surgery or trauma",
                                                   "Spinal malformation that makes the procedure infeasible",
                                                   "Signs of possible raised intracranial pressure (Neuroimaging or 
            clinical evidences)",
                                                   "INR greater 1.5 or Platelet counts less 50,000 mm^(-3)",
                                                  );

        $this->addLabel("");

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Contraindications to lumbar puncture"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Yes/No"
        );
        $this->form->addGroup(
            $group,
            "contraindications_to_l_p_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($contraindicationsToLumbarPunctureNames); $i++) {
            $group[] =& $this->createLabel($contraindicationsToLumbarPunctureNames[$i]);
            $group[] =& $this->createSelect(
                "contraindications_to_l_p_" . $i . "_yes_or_no",
                "contraindications_to_l_p_yes_or_no",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "contraindications_to_l_p_" . $i . "_yes_or_no",
                array("contraindications_to_l_p_" . $i . "_yes_or_no{@}=={@}"),
                "Required.",
                "contraindications_to_l_p_" . $i
            );
            $this->addGroup(
                $group,
                "contraindications_to_l_p_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

    }
}

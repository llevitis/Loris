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
 * Creates the form elements for the Screening Summary Diagnosis AD Mixed instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */

class NDB_BVL_Instrument_Screening_Summary_Diagnosis_AD_Mixed extends NDB_BVL_Instrument
{
    var $ValidityEnabled = false;
    var $ValidityRequired = false;

    /**
     * Sets up basic data, such as the LorisForm object, and so on.
     *
     * @param string $commentID the CommentID identifying the data to load
     * @param string $page if a multipage form, the page to show
     *
     * @return void
     * @access public
     */
    function setup($commentID, $page)
    {
        $this->formType = "XIN";
        $this->form = new LorisForm('Screening_Summary_Diagnosis_AD_Mixed_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = 'Screening_Summary_Diagnosis_AD_Mixed';           // test_names.Test_name
        $this->table = 'Screening_Summary_Diagnosis_AD_Mixed';              // name of database table corresponding to instrument
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

        $config = NDB_Config::singleton();
        $this->dateOptions = array(
            'language' => 'en',
            'format' => 'YMd',
            'minYear' => $config->getSetting('startYear'),
            'maxYear' => $config->getSetting('endYear'),
            'addEmptyOption' => true,
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
            "/Screening_Summary_Diagnosis_AD_Mixed(_page[0-9]+)/",
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
        $this->addHeader("Summary and Diagnosis");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

    }

    function _page1() {
        $this->addHeader("Summary and Diagnosis");

        $yesNoOptions = array(
            null => "",
            "yes" => "YES",
            "no" => "NO"
        );

        $q2Options = array(
            null => "",
            "no_previous_neurological_diagnosis" => "No previous neurological
            diagnosis",
            "young_healthy_control" => "Young Healthy Control (YHC)",
            "elderly_healthy_control" => "Elderly Healthy Control (EHC)",
            "subjective_cognitive_impairment" => "Subjective Cognitive
             Impairment (SCI)",
            "mild_cognitive_impairment" => "Mild Cognitive Impairment (MCI)",
            "mci_with_silent_vascular_lesions" => "Mild Cognitive Impairment with
            Silent Vascular Lesions (V-MCI)",
            "alzheimers_disease" => "Alzheimer's Disease (AD)"
        );

        $q3Options = array(
            null => "",
            "screening_test_battery" => "Screening test battery",
            "clinical_chart" => "Clinical chart",
            "other" => "Other (please specify)"
        );

        /** Q1 */

        $this->addLabel("<h4>1.</h4>");


        $this->addSelect(
            "q1_yes_no",
            "Has the participant met the general and disease-specific
            screening inclusion and exclusion criteria?",
            $yesNoOptions
        );
        $this->addTextElement(
            "q1_no_comment",
            "If NO, state the inclusion/exclusion criteria they
             did not meet:"
        );
        $this->XINRegisterRule(
            "q1_no_comment",
            array("q1_yes_no{@}=={@}no"),
            "Required if the answer is NO.",
            "q1_group"
        );

        /**  Q2 */

        $this->addLabel("<h4>2.</h4>");


        $this->addSelect(
            "q2_diagnosis",
            "What is the initial research diagnosis of the participant
            after the screening visit?",
            $q2Options
        );

        /** Q3 */

        $this->addLabel("<h4>3.</h4>");


        $this->addSelect(
            "q3_materials",
            "What materials were used in arriving at this diagnosis?",
            $q3Options
        );
        $this->addTextElement(
            "q3_other",
            "Other (please specify)"
        );
        $this->XINRegisterRule(
            "q3_other",
            array("q3_materials{@}=={@}other"),
            "Required if Other.",
            "q3_other_group"
        );

    }

    function _page2() {
        $this->addHeader("Summary and Diagnosis");

        $q5options = array(
            null => "",
            "physician" => "Physician",
            "research_nurse" => "Research Nurse",
            "research_coordinator" => "Research Coordinator",
            "research_assistant" => "Research Assistant"
        );

        /** Q4 */

        $this->addLabel("<h4>4.</h4>");


        $this->addTextElement(
            "q4",
            "If this diagnosis is a change from the referring clinical diagnosis
            (p.2), or if this was the first diagnosis applied, please comment on how
            the diagnosis was arrive at (e.g. met Weston Neuroinflammation research
            diagnostic criteria for MCI):"
        );


        /** Q5 */

        $this->addLabel("<h4>5.</h4>");

        $this->addSelect(
            "diagnostic_evaluator",
            "The diagnostic evaluation of the participant was completed by:",
            $q5options
        );
        $this->addTextElement(
            "diagnostic_evaluator_name",
            "Name:"
        );
        $this->addBasicDate(
            "diagnostic_evaluation_date",
            "Date:"
        );

    }
}
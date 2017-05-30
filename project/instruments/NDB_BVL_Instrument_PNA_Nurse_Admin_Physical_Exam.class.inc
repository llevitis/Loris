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
 * Creates the form elements for the PNA Nurse Admin Physical Exam instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */

class NDB_BVL_Instrument_PNA_Nurse_Admin_Physical_Exam extends NDB_BVL_Instrument
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
        $this->form = new LorisForm('PNA_Nurse_Admin_Physical_Exam_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = 'PNA_Nurse_Admin_Physical_Exam';           // test_names.Test_name
        $this->table = 'PNA_Nurse_Admin_Physical_Exam';              // name of database table corresponding to instrument
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
            "/PNA_Nurse_Admin_Physical_Exam(_page[0-9]+)/",
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
        $this->addHeader("Physical and Neurological Assessment: Nurse Administered Physical Exam");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

    }

    function _page1() {
        $this->addHeader("Physical and Neurological Assessment: Nurse Administered Physical Exam");

        $yesNoOptions = array(
            null => "",
            "no" => "No",
            "yes" => "Yes"
        );

        $symptomOptions = array(
            null => "",
            "mild" => "Mild",
            "moderate" => "Moderate",
            "severe" => "Severe"
        );

        $this->addLabel("<h4>1</h4>");

        $this->addSelect("EKG_done", "Resting EKG done at this visit?", $yesNoOptions);

        $this->addLabel("<h4>2</h4>");


        $symptomNames = array(
            "Drug allergic reaction/hypersensitivity",
            "Sinusitis",
            "Loss of sense of smell",
            "Pruritis",
            "Urticaria",
            "Pigmentation changes",
            "Erythema multiforme / rash / redness",
            "Bruising",
            "Petechiae / purpura",
            "Epistaxis",
            "Hemoptysis",
            "Hematemesis",
            "Melena",
            "Rectal bleeding",
            "Hematochezia",
            "Vaginal bleeding",
            "Hematuria",
            "Anemia",
            "Hemorrhage (other) specify:",
            "Sustained reduction in urinary output",
            "Incontinence",
            "Shortness of breath",
            "Peripheral oedema",
            "Unexplained weight gain",
            "Unexplained weight loss",
            "Dysphagia",
            "Dyspepsia",
            "Nausea",
            "Acid reflux",
            "Other abdominal pain",
            "Stomatitis / pharyngitis",
            "Vomiting",
            "Diarrhea",
            "Costovertebral angle tenderness in back",
            "Lower back pain",
            "Tinnitus",
            "Dizziness / vertigo",
            "Insomnia",
            "Headache",
            "Numbness / tingling",
            "Tremor / shakiness",
            "Falls",
            "Fainting",
            "Other #1 specify symptom:",
            "Other #2 specify symptom:"
        );



        for ($i = 0; $i < (count($symptomNames) - 2); $i++) {
            $group[] =& $this->createLabel($symptomNames[$i]);
            $group[] =& $this->createSelect(
                "symptom_names_" . $i,
                "symptom_severity",
                $symptomOptions
            );
            $this->XINRegisterRule(
                "symptom_names_" . $i,
                array("symptom_names_ . $i{@}=={@}NEVER_REQUIRED"),
                "Not required.",
                "symptom_names_group_$i"
            );
            $this->addGroup(
                $group,
                "symptom_names_group_$i",
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        for ($i = (count($symptomNames) - 2); $i < count($symptomNames); $i++) {
            $group[] =& $this->createLabel($symptomNames[$i]);
            $group[] =& $this->createText(
                "symptom_names_2_" . $i . "_label",
                "symptom_label"
            );
            $this->XINRegisterRule(
                "symptom_names_2_" . $i . "_label",
                array("symptom_names_2_" . $i . "_label{@}=={@}NEVER_REQUIRED"),
                "Not required.",
                "symptom_names_2_" . $i
            );
            $group[] =& $this->createSelect(
                "symptom_names_2_" . $i . "_severity",
                "symptom_severity",
                $symptomOptions
            );
            $this->XINRegisterRule(
                "symptom_names_2_" . $i . "_severity",
                array("symptom_names_2_" . $i . "_label{@}!={@}"),
                "Required if a symptom is specified for 'Other'.",
                "symptom_names_2_" . $i
            );
            $this->addGroup(
                $group,
                "symptom_names_2_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        $this->addLabel("<h4>3. Physical Examination.</h4>");
        $this->addSelect("PE_done", "Was there a physical examination completed at this visit?", $yesNoOptions);
        $this->addTextElement("PE_no", "If NO, reason:");
        $this->XINRegisterRule(
            "PE_no",
            array("PE_done{@}=={@}no"),
            "Required if physical examination was not completed at this visit.",
            "PE_no_group"
        );
        $this->addTextElement("PE_yes", "If YES, summary of physical exam:");
        $this->XINRegisterRule(
            "PE_yes",
            array("PE_done{@}=={@}yes"),
            "Required if physical examination was completed at this visit.",
            "PE_yes_group"
        );
    }

}

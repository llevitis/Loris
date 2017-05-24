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
 * Creates the form elements for the PNA Neurologist Admin Physical Exam instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */

class NDB_BVL_Instrument_PNA_Neurologist_Admin_Physical_Exam extends NDB_BVL_Instrument
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
        $this->form = new LorisForm('PNA_Neurologist_Admin_Physical_Exam_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = 'PNA_Neurologist_Admin_Physical_Exam';           // test_names.Test_name
        $this->table = 'PNA_Neurologist_Admin_Physical_Exam';              // name of database table corresponding to instrument
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
            "/PNA_Neurologist_Admin_Physical_Exam(_page[0-9]+)/",
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
        $this->addHeader("Physical and Neurological Assessment: Neurologist Administered Physical Exam");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

    }

    function _page1() {
        $this->addHeader("Physical and Neurological Assessment: Neurologist Administered Physical Exam");

        $physicalExaminationSites = array(
            "General appearance (hygiene, mobility, cooperation, speech, quality, mood)",
            "Skin (rashes, lesion, color, scars)",
            "Eyes (visual aids)",
            "Ears (hearing aids, otoscopic exam)",
            "Mouth (dentures, tongue, gum hygiene)",
            "Head and neck (inspection, lymph nodes, thyroid)",
            "Heart (rate, rhythm, murmur, pulses)",
            "Lung (auscultation, rales, wheezes, rhonchies)",
            "Abdomen (inspection, bowel sounds, tenderness, liver, mass)",
            "Musculoskeletal (edema, deformities, color, varicosities, strength, mass)"
        );

        $yesNoOptions = array(
            null => "",
            "no" => "No",
            "yes" => "Yes"
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
            "Abnormal"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "If abnormal, specify:"
        );


        $this->form->addGroup(
            $group,
            "physical_examination_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($physicalExaminationSites); $i++) {
            $group[] =& $this->createLabel($physicalExaminationSites[$i]);
            $group[] =& $this->createSelect(
                "physical_examination_" . $i . "_abnormal_or_normal",
                "pe_abnormal_or_normal",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "physical_examination_" . $i . "_abnormal_or_normal",
                array("physical_examination_" . $i . "_abnormal_or_normal{@}=={@}"),
                "Required.",
                "physical_examination_" . $i
            );
            $group[] =& $this->createText(
                "physical_examination_" . $i . "_comment",
                "pe_comment"
            );
            $this->XINRegisterRule(
                "physical_examination_" . $i . "_comment",
                array("physical_examination_" . $i . "_abnormal_or_normal{@}=={@}yes"),
                "Required if abnormal.",
                "physical_examination_" . $i
            );
            $this->addGroup(
                $group,
                "physical_examination_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        /* Rectal exam */

        $this->addSelect("4_rectal_exam", "4. Was a rectal examination done at this visit?", $yesNoOptions);

        /* Genital exam */

        $this->addSelect("5_genital_exam", "5. Was a genital examination done at this visit?", $yesNoOptions);

        /* Medical conditions */

        $this->addSelect(
            "6_conditions",
            "6. At this point, does the participant have any condition(s)
             that make it medically inappropriate to enroll in the program?",
            $yesNoOptions);
    }
}
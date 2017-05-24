<?php
/**
 * This file contains the NDB_BVL_Instrument_Everyday_Cognition
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
 * Creates the form elements for the Screening General Inclusion Criteria instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */
class NDB_BVL_Instrument_Screening_General_Inclusion_Criteria extends NDB_BVL_Instrument
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
        $this->form = new LorisForm('Screening_General_Inclusion_Criteria_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = 'Screening_General_Inclusion_Criteria';           // test_names.Test_name
        $this->table = 'Screening_General_Inclusion_Criteria';              // name of database table corresponding to instrument
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
            "/Screening_General_Inclusion_Criteria(_page[0-9]+)/",
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
        $this->addHeader("General Inclusion Criteria");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

    }

    function _page1() {
        $this->addHeader("General Inclusion Criteria");
        $yesNoOptions = array(
            null => "",
            "no" => "No",
            "yes" => "Yes"
        );

        $criteriaNames = array(
            "Weight < 136 kg",
            "At least 6 years of formal education or history of academic achievement and/or employment
            sufficient to exclude mental retardation",
            "Sufficient fluency in English and/or French",
            "Willing to undergo repeated (2 time points, 2 years a part) MRI and at least three PET scans
            (tau, amyloid, neuroinflammation).",
            "Agree to donate blood (for genetic testing), and CSF",
            "Geographic accessibility to the study site",
            "Visual and auditory acuity adequate for perform tests.",
            "Good general health with no uncontrolled diseases expected to interfere with the study",
            "Non-depressed (GDS < 6)",
            "Modified Hachinski less than or equal to 4",
            "High binder phenotype for TSPO rs6971 polymorphism"
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

        $this->addGroup(
            $group,
            "inclusion_criteria_headers",
            null,
            $this->_GUIDelimiter,
            false
        );

        for ($i = 0; $i < count($criteriaNames); $i++) {
            $group[] =& $this->createLabel($criteriaNames[$i]);
            $group[] =& $this->createSelect(
                "inclusion_criteria_" . $i,
                "yes_or_no",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "inclusion_criteria_" . $i,
                array("inclusion_criteria_  . $i{@}=={@}"),
                "A response is required."
            );
            $this->addGroup(
                $group,
                "inclusion_criteria_group_$i",
                null,
                $this->_GUIDelimiter,
                false
            );
        }


    }
}
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
 * Creates the form elements for the General Health Biosample Collection instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */

class NDB_BVL_Instrument_General_Health_Biosample_Collection extends NDB_BVL_Instrument
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
        $this->form = new LorisForm('General_Health_Biosample_Collection_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = 'General_Health_Biosample_Collection';           // test_names.Test_name
        $this->table = 'General_Health_Biosample_Collection';              // name of database table corresponding to instrument
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
            "/General_Health_Biosample_Collection(_page[0-9]+)/",
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
        $this->addHeader("Biosample Collection");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

    }

    function _page1()
    {
        $this->addHeader("Biosample Collection");

        $yesNoOptions = array(
            null => "",
            "yes" => "YES",
            "no" => "NO"
        );

        /** Blood sample */

        $this->addLabel("<h4>Blood sample (fasting)</h4>");
        $this->addBasicDate(
            "blood_sample_date",
            "1. Date collected:"
        );
        $this->addBasicText(
            "blood_sample_time_of_collection",
            "2. Time of collection (24h):"
        );
        $this->addSelect(
            "blood_sample_fasting_yes_no",
            "3. Fasting >= 12h",
            $yesNoOptions
        );
        $this->addBasicText(
            "blood_sample_time_of_last_meal",
            "4. Time of last meal (24h):"
        );
        $this->addBasicText(
            "blood_sample_fasting_period",
            "5. Fasting period (hours):"
        );

        /** Buccal sample */
        $this->addLabel("<h4>Buccal sample</h4>");
        $this->addBasicDate(
            "buccal_sample_date",
            "1. Date:"
        );
        $this->addBasicText(
            "buccal_sample_time_of_collection",
            "2. Time of collection (24h):"
        );

        /** Urine sample */
        $this->addLabel("<h4>Urine sample</h4>");
        $this->addBasicDate(
            "urine_sample_date",
            "1. Date collected:"
        );
        $this->addBasicText(
            "urine_sample_time_of_collection",
            "2. Time of collection (24h):"
        );

        /** Hair sample */

        $this->addLabel("<h4>Hair sample</h4>");
        $this->addBasicDate(
            "hair_sample_date",
            "Date collected;"
        );
        $this->addBasicText(
            "hair_sample_time_of_collection",
            "Time of collection (24h):"
        );

        /** Saliva sample (>= 30 min after eating) */
        $this->addLabel("<h4>Saliva sample (>= 30 min after eating)</h4>");
        $this->addBasicDate(
            "saliva_sample_date",
            "Date collected:"
        );
        $this->addBasicText(
            "saliva_sample_time_of_collection",
            "Time of collection (24h):"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Time elapsed since last meal"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "min or hours"
        );
        $this->form->addGroup(
            $group,
            "saliva_sample_part3_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        $group[] =& $this->createText(
            "saliva_sample_time_elapsed_since_last_meal",
            ""
        );
        $group[] =& $this->createSelect(
            "saliva_sample_time_elapsed_unit",
            "",
            array(
                null => "",
                "min" => "min",
                "hours" => "hours"
            )
        );
        $this->XINRegisterRule(
            "saliva_sample_time_elapsed_unit",
            array("saliva_sample_time_elapsed_since_last_meal{@}!={@}"),
            "Unit of time must be specified.",
            "saliva_sample_time_elapsed_group"
        );
        $this->addGroup(
            $group,
            "saliva_sample_time_elapsed_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        /** Fecal sample */

        $this->addLabel("<h4>Fecal sample</h4>");
        $this->addBasicDate(
            "fecal_sample_date",
            "Date collected:"
        );
        $this->addBasicText(
            "fecal_sample_time_of_collection",
            "Time of collection (24h):"
        );
        $this->addBasicText(
            "fecal_sample_time_elapsed_since_collection",
            "Time elapsed since collection and sample return to clinic (hours):"
        );
    }


    function _page2() {
        $this->addHeader("Biosample Collection");

        $this->addSelect(
            "glucose",
            "Glucose (check only one)",
            array(
                null => "",
                "normal" => "Normal",
                "1+50mg/dl" => "1 + 50 mg/dl",
                "2+100mg/dl" => "2 + 100 mg/dl",
                "3+300mg/dl" => "3 + 300 mg/dl",
                "4+1000mg/dl" => "4 + 1000 mg/dl",
                "not_done" => "Not done"
            )
        );

        $this->addSelect(
            "protein",
            "Protein (check only one)",
            array(
                null => "",
                "negative" => "Negative",
                "1+30mg/dl" => "1 + 30 mg/dl",
                "2+100mg/dl" => "2 + 100 mg/dl",
                "3+500mg/dl" => "3 + 500 mg/dl",
                "not_done" => "Not done"
            )
        );
    }
}
<?php
/**
 * This file contains the NDB_BVL_Instrument_Functional_Activity
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
 * Creates the form elements for the Functional Activity instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */

class NDB_BVL_Instrument_Functional_Activity extends NDB_BVL_Instrument
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
        $this->form = new LorisForm('Functional_Activity_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = 'Functional_Activity';           // test_names.Test_name
        $this->table = 'Functional_Activity';              // name of database table corresponding to instrument
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
            "/Functional_Activity(_page[0-9]+)/",
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
        $this->addHeader("Functional Activity");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

        $score_columns = array("total_score" => "Total Score");
        while ($i = current($score_columns)) {
            $this->addScoreColumn(
                key($score_columns),
                $i
            );
            next($score_columns);
        }


    }

    function _page1() {
        $this->addHeader("Functional Activity");

        $scaleOptions = array(
            null => "",
            0 => "0",
            1 => "1",
            2 => "2",
            3 => "3"
        );

        $questions = array(
            "Writing checks, paying bills, balancing checkbook",
            "Assembling tax records, business affairs, or papers",
            "Shopping alone for clothes, household necessities, or groceries",
            "Playing a game of skill, working on a hobby",
            "Heating water, making a cup of coffee, turning off stove after use",
            "Preparing a balanced meal",
            "Keeping track of current events",
            "Paying attention to, understanding, discussing TV, book, magazine",
            "Remembering appointments, family occasions, holidays, medications",
            "Traveling out of neighborhood, driving, arranging to take buses"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Ask informant to rate patient's ability."
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Score"
        );
        $this->form->addGroup(
            $group,
            "functional_activity_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);



        for ($i = 0; $i < count($questions); $i++) {
            $group[] =& $this->createLabel($questions[$i]);
            $group[] =& $this->createSelect(
                "functional_activity_" . $i,
                "Ability",
                $scaleOptions
            );
            $this->XINRegisterRule(
                "functional_activity_" . $i,
                array("functional_activity_ . $i{@}=={@}"),
                "This question is required.",
                "functional_activity_group_$i"
            );
            $this->addGroup(
                $group,
                "functional_activity_group_$i",
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

    }

    function score() {
        if ($this->_determineDataEntryCompletionStatus() == "Incomplete") {
            return;
        }

        $db =& Database::singleton();
        //Get raw questions point values
        $query = "SELECT * FROM " . $this->table .
            " WHERE CommentID='" . $this->getCommentID() . "'";
        $record = $db->pselectRow($query, null);
        $candidate = Candidate::singleton($_REQUEST['candID']);
        $score = array();

        $score["total_score"] = 0;
        for ($i = 0; $i < 10; $i++) {
            $score["total_score"] += $record["functional_activity_" . $i];
        }

        $db->update(
            $this->table,
            $score,
            array('CommentID'=>$this->getCommentID())
        );

    }


}


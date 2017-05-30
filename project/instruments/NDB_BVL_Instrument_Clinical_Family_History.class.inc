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
 * Creates the form elements for the Clinical Family History instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */

class NDB_BVL_Instrument_Clinical_Family_History extends NDB_BVL_Instrument
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
        $this->form = new LorisForm('Clinical_Family_History_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = 'Clinical_Family_History';           // test_names.Test_name
        $this->table = 'Clinical_Family_History';              // name of database table corresponding to instrument
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
            "/Clinical_Family_History(_page[0-9]+)/",
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
        $this->addHeader("Family History");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

    }

    function _page1()
    {
        $this->addHeader("Family History");

        $yesNoOptions = array(
            null => "",
            "yes" => "Yes",
            "no" => "No"
        );

        $yesNoUnknownOptions = array(
            null => "",
            "yes" => "Yes",
            "no" => "No",
            "unknown" => "Unknown"
        );

        /** Family History of AD */

        $this->addSelect(
            "family_history_ad",
            "Family History of AD:",
            $yesNoUnknownOptions
        );

        /** AD sibling */

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "AD sibling (Yes/No):"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "If yes, how many"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Age(s) of unset:"
        );
        $this->form->addGroup(
            $group,
            "ad_sibling_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        $group[] =& $this->createSelect(
            "ad_sibling_yes_or_no",
            "AD sibling",
            $yesNoOptions
        );
        $group[] =& $this->createText(
            "ad_sibling_amount",
            "AD sibling amount"
        );
        $group[] =& $this->createText(
            "ad_sibling_age_onset",
            "AD sibling - age(s) of onset"
        );
        $this->XINRegisterRule(
            "ad_sibling_yes_or_no",
            array("ad_sibling_yes_or_no{@}=={@}"),
            "Required.",
            "ad_sibling_group"
        );
        $this->XINRegisterRule(
            "ad_sibling_amount",
            array("ad_sibling_yes_or_no{@}=={@}yes"),
            "Number of AD sibling(s) must be specified if selected 'yes'",
            "ad_sibling_group"
        );
        $this->XINRegisterRule(
            "ad_sibling_age_onset",
            array("ad_sibling_amount{@}!={@}"),
            "Age(s) of onset must be specified.",
            "ad_sibling_group"
        );
        $this->addGroup(
            $group,
            "ad_sibling_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);


        /** AD father & mother */

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
            "Yes/No/Unknown"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Age of onset"
        );
        $this->form->addGroup(
            $group,
            "ad_parent_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        $parents_AD = array(
            "AD mother",
            "AD father");

        for ($i = 0; $i < count($parents_AD); $i++) {
            $group[] =& $this->createLabel($parents_AD[$i]);
            $group[] =& $this->createSelect(
                "ad_" . $i . "_yes_no_unknown",
                "yes_no_unknown",
                $yesNoUnknownOptions
            );
            $group[] =& $this->createText(
                "ad_" . $i . "_age_of_onset",
                "age_of_onset"
            );
            $this->XINRegisterRule(
                "ad_" . $i . "_yes_no_unknown",
                array("ad_" . $i . "_yes_no_unknown{@}=={@}"),
                "Required.",
                "ad_" . $i
            );
            $this->XINRegisterRule(
                "ad_" . $i . "_age_of_onset",
                array("ad_" . $i . "_yes_no_unknown{@}=={@}yes"),
                "Age of onset must be specified.",
                "ad_" . $i
            );
            $this->addGroup(
                $group,
                "ad_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        /** Family history of ND */

        $this->addSelect(
            "family_history_nd",
            "Family History of ND:",
            $yesNoUnknownOptions
        );

        /** Sibling history of ND */

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "ND sibling (Yes/No):"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "If yes, how many"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Age(s) of unset:"
        );
        $this->form->addGroup(
            $group,
            "nd_sibling_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        $group[] =& $this->createSelect(
            "nd_sibling_yes_or_no",
            "ND sibling",
            $yesNoOptions
        );
        $group[] =& $this->createText(
            "nd_sibling_amount",
            "ND sibling amount"
        );
        $group[] =& $this->createText(
            "nd_sibling_age_onset",
            "ND sibling - age(s) of onset"
        );
        $this->XINRegisterRule(
            "nd_sibling_yes_or_no",
            array("nd_sibling_yes_or_no{@}=={@}"),
            "Required.",
            "nd_sibling_group"
        );
        $this->XINRegisterRule(
            "nd_sibling_amount",
            array("nd_sibling_yes_or_no{@}=={@}yes"),
            "Number of ND sibling(s) must be specified if selected 'yes'",
            "nd_sibling_group"
        );
        $this->XINRegisterRule(
            "nd_sibling_age_onset",
            array("nd_sibling_amount{@}!={@}"),
            "Age(s) of onset must be specified.",
            "nd_sibling_group"
        );
        $this->form->addGroup(
            $group,
            "nd_sibling_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        /** Parent History of ND */


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
            "Yes/No/Unknown"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Age of onset"
        );
        $this->form->addGroup(
            $group,
            "nd_parent_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        $parents_ND = array(
            "ND mother",
            "ND father");

        for ($i = 0; $i < count($parents_ND); $i++) {
            $group[] =& $this->createLabel($parents_ND[$i]);
            $group[] =& $this->createSelect(
                "nd_" . $i . "_yes_no_unknown",
                "yes_no_unknown",
                $yesNoUnknownOptions
            );
            $group[] =& $this->createText(
                "nd_" . $i . "_age_of_onset",
                "age_of_onset"
            );
            $this->XINRegisterRule(
                "nd_" . $i . "_yes_no_unknown",
                array("nd_" . $i . "_yes_no_unknown{@}=={@}"),
                "Required.",
                "nd_" . $i
            );
            $this->XINRegisterRule(
                "nd_" . $i . "_age_of_onset",
                array("nd_" . $i . "_yes_no_unknown{@}=={@}yes"),
                "Age of onset must be specified.",
                "nd_" . $i
            );
            $this->addGroup(
                $group,
                "nd_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        /** Description of family members with ND */

        $this->addTextElement(
            "description_family_members_nd",
            "Description of family members with ND:"
        );
    }
}



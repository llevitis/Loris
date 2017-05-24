<?php
/**
 * This file contains the NDB_BVL_Instrument_MAYONNAISE
 * class
 *
 * PHP Version 5
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   David Blader <dblader.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */
/**
 * Creates the form elements for the MAYONNAISE instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   David Blader <dblader.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */
class NDB_BVL_Instrument_MAYONNAISE extends NDB_BVL_Instrument
{
    var $ValidityEnabled = false;
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
        $this->formType = 'XIN';
        $this->form = new LorisForm('MAYONNAISE_form');
        $this->page = $page;
        // set the object properties
        $this->testName = 'MAYONNAISE'; // MAYONNAISEs.MAYONNAISE
        $this->table = 'MAYONNAISE'; // name of database table corresponding to instrument
        $this->commentID = $commentID; // data keyed by commentID
        //The array of dates/timestamps to convert to database dates/timestamps
        //Any LorisForm date elements must be listed here
        $this->dateTimeFields = array("Date_taken");
        //The array of selects with multiple answers allowed
        //Any LorisForm multiple selects must be listed here
        //$this->_selectMultipleElements = array();
        // required fields for data entry completion status
        $this->_requiredElements = array(
            'Examiner',
            'CommentID'
        );
        $config = NDB_Config::singleton();
        $this->dateOptions = array(
            'language' => 'en',
            'format' => 'YMd',
            'minYear' => $config->getSetting('startYear'),
            'maxYear' => $config->getSetting('endYear'),
            'addEmptyOption' => true,
            'emptyOptionValue' => null
        );
        // setup the form
        $this->_setupForm();
    }
    /**
     * Method to build the LorisForm object into a paged form
     *
     * @return void
     * @access private
     */
    function _setupForm()
    {
        //determine page to display
        if (preg_match("/MAYONNAISE(_page[0-9]+)/",
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
     * Generates the main page of the form.
     *
     * @return void
     * @access private
     */
    function _main()
    {
        // display test name
        $this->addHeader("Kool & Awesome LORIS Instrument 4 Educational Purposez");
        $this->_addMetadataFields();
    }
    /**
     * Page 1
     *
     * @return void
     */
    function _page1()
    {
        $yesNoOptions = array(
            null  => "",
            "yes" => "Yes",
            "no"  => "No",
        );
        // Header
        $this->addHeader("Kool & Awesome LORIS Instrument 4 Educational Purposez");
        $this->addTextElement("Name", "What's your name?");
        $options = array("Im_a_what" => "I'm a what", "Oooohh_hell_yes" => "Oooohh hell yes", "OK" => "OK", "Other" => "Other");
        $this->addSelect("Wizard", "Yer a wizard, Harry?", $options);
        $this->addTextElement("Other", "If Other, please specify");
        $this->XINRegisterRule("Other", array("Wizard{@}=={@}Other"), "Required.", "Other_group");
        $this->addYesNoElement("Mayo", "Is mayonnaise an instrument?");
        $options2 = array("Cool" => "Cool", "Fun" => "Fun", "Talented" => "Talented", "Nice" => "Nice", "OK" => "He is just OK / kind of overrated");
        $this->addSelect("David", "David is (please select all that apply):", $options2, ["multiple"]);
        $this->addNumericElement("Favourite", "What's your favourite number?");
        $this->addDateElement("Birthday", "When's your birthday?");

        // Table headers
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Incident"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Hospitalized?"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Age"
        );
        $this->form->addGroup(
            $group,
            "concussion_titles",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        // data entry fields
        for ($i = 1; $i < 4; $i++) {
            $group[] =& $this->createText(
                "concussion_" . $i . "_description",
                "Incident"
            );
            $this->XINRegisterRule(
                "concussion_" . $i . "_description",
                array("concussion_" . $i . "_description{@}=={@}NEVER_REQUIRED"),
                "Required."
            );
            $group[] =& $this->createText(
                "concussion_" . $i . "_hospitalized",
                "Hospitalized?"
              ##  $yesNoOptions
            );
            $this->XINRegisterRule(
                "concussion_" . $i . "_hospitalized",
                array("concussion_" . $i . "_hospitalized{@}=={@}NEVER_REQUIRED"),
                "Required."
            );
            $group[] =& $this->createText(
                "concussion_" . $i . "_age",
                "Age"
            );
            $this->XINRegisterRule(
                "concussion_" . $i . "_age",
                array("concussion_" . $i . "_age{@}=={@}NEVER_REQUIRED"),
                "Required."
            );
            $this->form->addGroup(
                $group,
                "concussion_table_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }
    }

}
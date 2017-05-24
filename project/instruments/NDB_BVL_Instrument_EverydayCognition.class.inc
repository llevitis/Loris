<?php
/**
 * This file contains the NDB_BVL_Instrument_EverydayCognition
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
 * Creates the form elements for the Everyday Cognition instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */
class NDB_BVL_Instrument_Everyday_Cognition extends NDB_BVL_Instrument
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
        $this->form = new LorisForm('Everyday_Cognition_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = 'Everyday_Cognition';           // test_names.Test_name
        $this->table = 'Everyday_Cognition';              // name of database table corresponding to instrument
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
            'CommentID');

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
        if (preg_match("/Everyday_Cognition(_page[0-9]+)/",
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
     *
     */
    function _main(){
        // display test name
        $this->addHeader("Everyday Cognition");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
    }

    function _page1() {
        $this->addHeader("Everyday Cognition");
        $this->addLabel("Memory");

        $Memory_Questions = array(
            "1. Remembering a few shopping items without a list.",
            "2. Remembering things that happened recently (such as recent outings, events in the news).",
            "3. Recalling conversations a few days later.",
            "4. Remembering where he/she has placed objects.",
            "5. Repeating stories and/or questions.",
            "6. Remembering the current date or day of the week.",
            "7. Remembering he/she has already told someone something.",
            "8. Remembering appointments, meetings, or engagements."
        );

        $scaleOptions = array(
            null => "",
            "1" => "1 - BETTER OR NO CHANGE",
            "2" => "2 - QUESTIONABLE/OCCASIONALLY WORSE",
            "3" => "3 - CONSISTENTLY A LITTLE WORSE",
            "4" => "4 - CONSISTENTLY MUCH WORSE",
            "5" => "5 - I DON'T KNOW"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Rate amount of change."
        );
        $this->form->addGroup(
            $group,
            "memory_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 1; $i < 9; $i++) {
            $group[] =& $this->createLabel($Memory_Questions[$i-1]);
            $group[] =& $this->createSelect(
                "memory_" . $i,
                "Rate the amount of change on a five-point scale.",
                $scaleOptions
            );
        }
    }

    function _page2()
    {
        $this->addHeader("Everyday Cognition");
        $this->addLabel("Language");

        $Language_Questions = array(
            "1. Forgetting the names of objects.",
            "2. Verbally giving instructions to others.",
            "3. Finding the right words to use in a conversation.",
            "4. Communicating thoughts in a conversation.",
            "5. Following a story in a book or on TV.",
            "6. Understanding the point of what other people are trying to say.",
            "7. Remembering the meaning of common words.",
            "8. Describing a program he/she has watched on TV.",
            "9. Understanding spoken directions or instructions."
        );

        $scaleOptions = array(
            null => "",
            "1" => "1 - BETTER OR NO CHANGE",
            "2" => "2 - QUESTIONABLE/OCCASIONALLY WORSE",
            "3" => "3 - CONSISTENTLY A LITTLE WORSE",
            "4" => "4 - CONSISTENTLY MUCH WORSE",
            "5" => "5 - I DON'T KNOW"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Rate amount of change."
        );
        $this->addGroup(
            $group,
            "language_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 1; $i < 10; $i++) {
            $group[] =& $this->createLabel($Language_Questions[$i - 1]);
            $group[] =& $this->createSelect(
                "language_" . $i,
                "Rate the amount of change on a five-point scale.",
                $scaleOptions
            );
        }

        $this->addLabel("Visual-Spatial and Perceptual Abilities");

        $Visual_Spatial_Perceptual_Questions = array(
            "1. Following a map to find a new location.",
            "2. Reading a map and helping with directions when someone else is driving.",
            "3. Finding one's car in a parking lot.",
            "4. Finding the way back to a meeting spot in the mall or other location.",
            "5. Finding his/her way around a familiar neighborhood.",
            "6. Finding his/her way around a familiar store.",
            "7. Finding his/her way around a house visited many times."
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Rate amount of change."
        );
        $this->addGroup(
            $group,
            "visual_spatial_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 1; $i < 8; $i++) {
            $group[] =& $this->createLabel($Visual_Spatial_Perceptual_Questions[$i - 1]);
            $group[] =& $this->createSelect(
                "visual_spatial_" . $i,
                "Rate the amount of change on a five-point scale.",
                $scaleOptions
            );
        }
    }

    function _page3() {
        $this->addHeader("Everyday Cognition");
        $scaleOptions = array(
            null => "",
            "1" => "1 - BETTER OR NO CHANGE",
            "2" => "2 - QUESTIONABLE/OCCASIONALLY WORSE",
            "3" => "3 - CONSISTENTLY A LITTLE WORSE",
            "4" => "4 - CONSISTENTLY MUCH WORSE",
            "5" => "5 - I DON'T KNOW"
        );

        $this->addLabel("Executive Functioning: Planning");

        $EF_Planning_Questions = array(
            "1. Planning the sequence of stops on a shopping trip.",
            "2. The ability to anticipate weather changes and plan accordingly (i.e.,
                bring a coat or umbrella).",
            "3. Developing a schedule in advance of anticipated events.",
            "4. Thinking things through before acting.",
            "5. Thinking ahead.",
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Rate amount of change."
        );
        $this->addGroup(
            $group,
            "ef_planning_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 1; $i < 6; $i++) {
            $group[] =& $this->createLabel($EF_Planning_Questions[$i-1]);
            $group[] =& $this->createSelect(
                "ef_planning_" . $i,
                "Rate the amount of change on a five-point scale.",
                $scaleOptions
            );
        }

        $this->addLabel("Executive Functioning: Organization");
        $EF_Organization_Questions = array(
            "1. Keep living and work space organized.",
            "2. Balancing the checkbook without error.",
            "3. Keeping financial records organized.",
            "4. Prioritizing tasks by importance.",
            "5. Keeping mail and papers organized.",
            "6. Using an organized strategy to manage a medication schedule involving
            medical medications."
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Rate amount of change."
        );
        $this->addGroup(
            $group,
            "ef_organization_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 1; $i < 7; $i++) {
            $group[] =& $this->createLabel($EF_Organization_Questions[$i-1]);
            $group[] =& $this->createSelect(
                "ef_organization_" . $i,
                "Rate the amount of change on a five-point scale.",
                $scaleOptions
            );
        }

        $this->addLabel("Executive Functioning: Divided Attention");
        $EF_Attention_Questions = array(
            "1. The ability to do two things at once.",
            "2. Returning to a task after being interrupted.",
            "3. The ability to concentrate on a task without being distracted by external
            things in the environment.",
            "4. Cooking or working and talking at the same time."
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Rate amount of change."
        );
        $this->addGroup(
            $group,
            "ef_attention_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 1; $i < 5; $i++) {
            $group[] =& $this->createLabel($EF_Attention_Questions[$i-1]);
            $group[] =& $this->createSelect(
                "ef_attention_" . $i,
                "Rate the amount of change on a five-point scale.",
                $scaleOptions
            );
        }

    }

}








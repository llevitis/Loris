<?php
/**
 * This file contains the NDB_BVL_Instrument_CHOCOLATE
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
 * Creates the form elements for the CHOCOLATE instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */
class NDB_BVL_Instrument_CHOCOLATE extends NDB_BVL_Instrument
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
        $this->form = new LorisForm('CHOCOLATE_form');
        $this->page = $page;
        // set the object properties
        $this->testName = 'CHOCOLATE'; // MAYONNAISEs.MAYONNAISE
        $this->table = 'CHOCOLATE'; // name of database table corresponding to instrument
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
        if (preg_match("/CHOCOLATE(_page[0-9]+)/",
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
        $this->addHeader("Summer 2017 Example Instrument with Tables");
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

    }
}
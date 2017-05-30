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
 * Creates the form elements for the Patient Personal Information instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */

class NDB_BVL_Instrument_Patient_Personal_Information extends NDB_BVL_Instrument
{
    var $ValidityEnabled  = false;
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
        $this->formType = "XIN";
        $this->form     = new LorisForm('Patient_Personal_Information_form');
        $this->page     = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = 'Patient_Personal_Information';           // test_names.Test_name
        $this->table    = 'Patient_Personal_Information';              // name of database table corresponding to instrument
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

        $config            = NDB_Config::singleton();
        $this->dateOptions = array(
                              'language'         => 'en',
                              'format'           => 'YMd',
                              'minYear'          => $config->getSetting('startYear'),
                              'maxYear'          => $config->getSetting('endYear'),
                              'addEmptyOption'   => true,
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
            "/Patient_Personal_Information(_page[0-9]+)/",
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
        $this->addHeader("Patient Personal Information");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

    }

    function _page1()
    {
        $this->addHeader("Patient Personal Information");

        $yesNoOptions = array(
                         null  => "",
                         "yes" => "Yes",
                         "no"  => "No",
                        );

        $this->addSelect(
            "gender",
            "Gender:",
            array(
             null     => "",
             "male"   => "Male",
             "female" => "Female",
            )
        );

        $this->addSelect(
            "handedness",
            "Handedness:",
            array(
             null    => "",
             "left"  => "Left",
             "right" => "Right",
            )
        );

        $this->addTextElement(
            "years_formal_education",
            "Years of formal education:"
        );

        $this->addTextElement(
            "primary_occupation",
            "Primary occupation for most of life:"
        );
        $this->addTextElement(
            "most_recent_occupation",
            "Most recent occupation:"
        );

        /** Retirement */

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Retired?"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Retirement date:"
        );
        $this->form->addGroup(
            $group,
            "retirement_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        $group[] =& $this->createSelect(
            "retirement_status",
            "Retired?",
            $yesNoOptions
        );
        $group[] =& $this->createText(
            "retirement_date",
            "Retirement date:"
        );
        $this->XINRegisterRule(
            "retirement_status",
            array("retirement{@}=={@}"),
            "Required.",
            "retirement_group"
        );
        $this->XINRegisterRule(
            "retirement_date",
            array("retirement_status{@}=={@}yes"),
            "Retirement date must be specified if answered 'yes'.",
            "retirement_group"
        );
        $this->form->addGroup(
            $group,
            "retirement_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        /**
 * Type of participant residence
*/

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Type of participant residence:"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "If Other, specify:"
        );
        $this->form->addGroup(
            $group,
            "participant_residence_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        $group[] =& $this->createSelect(
            "type_of_participant_residence",
            "participant_residence",
            array(
             null                       => "",
             "house"                    => "House",
             "condo_co-op_owned"        => "Condo/Co-op (owned)",
             "apartment_rented"         => "Apartment (rented)",
             "mobile_home"              => "Mobile Home",
             "retirement_community"     => "Retirement Community",
             "assisted_living"          => "Assisted Living",
             "skilled_nursing_facility" => "Skilled Nursing Facility",
             "other"                    => "Other",
            )
        );
        $group[] =& $this->createText(
            "residence_other",
            "Other:"
        );
        $this->XINRegisterRule(
            "type_of_participant_residence",
            array("type_of_participant_residence{@}=={@}"),
            "Required.",
            "participant_residence_group"
        );
        $this->XINRegisterRule(
            "residence_other",
            array("type_of_participant_residence{@}=={@}other"),
            "Other type of residence must be specified if selected 'other'.",
            "participant_residence_group"
        );
        $this->form->addGroup(
            $group,
            "participant_residence_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);



        /** Primary Language */


        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Primary Language:"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "If Other, specify:"
        );
        $this->form->addGroup(
            $group,
            "primary_language_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);


        $group[] =& $this->createSelect(
            "primary_language",
            "Primary Language",
            array(
                null      => "",
                "english" => "English",
                "french"  => "French",
                "spanish" => "Spanish",
                "other"   => "Other, specify:",
            )
        );
        $group[] =& $this->createText(
            "primary_language_other",
            "Primary Language (Other):"
        );
        $this->XINRegisterRule(
            "primary_language",
            array("primary_language{@}=={@}"),
            "Primary language must be specified.",
            "primary_language_group"
        );
        $this->XINRegisterRule(
            "primary_language_other",
            array("primary_language{@}=={@}other"),
            "Other language must be specified if selected 'other'.",
            "primary_language_group"
        );
        $this->form->addGroup(
            $group,
            "primary_language_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        /** Language for testing */

        $this->addTextElement(
            "language_for_testing",
            "Language to be used for testing the participant"
        );

        /** AD symptoms onset */

        $this->addTextElement(
            "year_onset_AD_symptoms",
            "Year of onset of AD symptoms (best estimate (if applicable)):"
        );

        /** Alcohol consumption */

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Alcohol consumption"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Per week/month/year"
        );
        $this->form->addGroup(
            $group,
            "alcohol_consumption_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        $group[] =& $this->createText(
            "alcohol_consumption_amount",
            "Alcohol consumption"
        );
        $group[] =& $this->createSelect(
            "alcohol_consumption_frequency",
            "Per: ",
            array(
             null    => "",
             "week"  => "Week",
             "month" => "Month",
             "year"  => "Year",
            )
        );
        $this->XINRegisterRule(
            "alcohol_consumption_amount",
            array("alcohol_consumption_amount{@}=={@}"),
            "Alcohol consumption must be specified.",
            "alcohol_consumption_group"
        );
        $this->XINRegisterRule(
            "alcohol_consumption_frequency",
            array("alcohol_consumption_amount{@}!={@}"),
            "Specify whether this is the amount consumed per week, month, or year.",
            "alcohol_consumption_group"
        );
        $this->form->addGroup(
            $group,
            "alcohol_consumption_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);


        /** Smoking  */

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Smoking: "
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "If stopped, since when:"
        );
        $this->form->addGroup(
            $group,
            "smoking_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);


        $group[] =& $this->createSelect(
            "smoking_status",
            "Smoking:",
            array(
             null      => "",
             "yes"     => "Yes",
             "no"      => "No",
             "stopped" => "Stopped",
            )
        );
        $group[] =& $this->createText(
            "smoking_stopped_date",
            "Stopped Smoking Date"
        );
        $this->XINRegisterRule(
            "smoking_status",
            array("smoking_status{@}=={@}"),
            "Smoking status must be specified.",
            "smoking_group"
        );
        $this->XINRegisterRule(
            "smoking_stopped_date",
            array("smoking_status{@}=={@}stopped"),
            "Smoking date is required if selected 'stopped'.",
            "smoking_group"
        );
        $this->form->addGroup(
            $group,
            "smoking_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);
    }

    function _page2()
    {
        $this->addHeader("Patient Personal Information");

        $this->addTextElement(
            "ethnic_category",
            "Ethnic category:"
        );

        /** Racial category */

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Racial category:"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Other"
        );
        $this->form->addGroup(
            $group,
            "racial_category_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        $group[] =& $this->createSelect(
            "racial_category",
            "Racial Category",
            array(
             null                                => "",
             "american_indian_or_alaskan_native" => "American Indian or Alaskan Native",
             "asian"                             => "Asian",
             "black_or_african_american"         => "Black or African American",
             "white"                             => "White",
             "native_hawaiian_pacific_islander"  => "Native Hawaiian or other Pacific Islander",
             "arab"                              => "Arab",
             "unknown"                           => "Unknown",
             "other"                             => "Other",
            )
        );

        $group[] =& $this->createText(
            "racial_other",
            "Other: "
        );
        $this->XINRegisterRule(
            "racial_category",
            array("racial_category{@}=={@}"),
            "Racial category must be specified.",
            "racial_category_group"
        );
        $this->XINRegisterRule(
            "racial_other",
            array("racial_category{@}=={@}other"),
            "'Other' must be specified if selected.",
            "racial_category_group"
        );
        $this->form->addGroup(
            $group,
            "racial_category_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);
    }

}

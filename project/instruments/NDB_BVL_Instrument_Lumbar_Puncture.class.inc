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
 * Creates the form elements for the Lumbar Puncture instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */

class NDB_BVL_Instrument_Lumbar_Puncture extends NDB_BVL_Instrument
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
        $this->form     = new LorisForm('Lumbar_Puncture_form');
        $this->page     = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = 'Lumbar_Puncture';           // test_names.Test_name
        $this->table    = 'Lumbar_Puncture';              // name of database table corresponding to instrument
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
            "/Lumbar_Puncture(_page[0-9]+)/",
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
        $this->addHeader("Lumbar Puncture");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

    }

    function _page1()
    {
        $this->addHeader("Lumbar Puncture");

        $yesNoOptions = array(
                         null  => "",
                         "yes" => "YES",
                         "no"  => "NO",
                        );

        $this->addLabel("<h3>1. Date of lumbar puncture</h3>");
        $this->addBasicDate(
            "lumbar_puncture_date",
            "Date:"
        );

        $this->addLabel("<h3>2. Checklist</h3>");

        $checklistOptions = array(
                             "Focal neurological sign",
                             "Recent seizures",
                             "Papilledema",
                             "Skin irritation or infection",
                             "Platelets > 500.000",
                             "INR < 1.5",
                             "MRI/CT suggestive of HICP",
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
            "YES/NO"
        );
        $this->form->addGroup(
            $group,
            "checklist_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($checklistOptions); $i++) {
            $group[] =& $this->createLabel($checklistOptions[$i]);
            $group[] =& $this->createSelect(
                "checklist_" . $i . "_yes_or_no",
                "",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "checklist_" . $i . "_yes_or_no",
                array("checklist_" . $i . "_yes_or_no{@}=={@}"),
                "Required.",
                "checklist_" . $i
            );
            $this->addGroup(
                $group,
                "checklist_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        $this->addLabel("<h3>3. Clinical data</h3>");
        $this->addBasicText(
            "bp",
            "BP = "
        );
        $this->addBasicText(
            "cf",
            "CF (bpm): "
        );
        $this->addSelect(
            "blood_sample_collected_glucose_protein",
            "Blood sample collected glucose protein / proteinogram",
            $yesNoOptions
        );
        $this->addSelect(
            "clinical_history_migraines_headaches",
            "Clinical history of migraines, headaches",
            $yesNoOptions
        );

    }

    function _page2()
    {
        $this->addHeader("Lumbar Puncture");

        $this->addLabel("<h3>Procedures</h3>");

        $yesNoOptions = array(
                         null  => "",
                         "yes" => "Yes",
                         "no"  => "No",
                        );

        $procedures = array(
                       "Signed consent form",
                       "Positioning",
                       "Skin sterilization with chorhexidine",
                       "Local anesthesia with lidocaine 1%",
                       "L3/L4",
                       "L4/L5 invertebral space",
                       "Introducer",
                       "24G Sprotte spinal needle",
                       "Unsuccessful trials",
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
        $this->form->addGroup(
            $group,
            "procedures_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);
        for ($i = 0; $i < count($procedures); $i++) {
            $group[] =& $this->createLabel($procedures[$i]);
            $group[] =& $this->createSelect(
                "procedures_" . $i . "_yes_or_no",
                "",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "procedures_" . $i . "_yes_or_no",
                array("procedures_" . $i . "_yes_or_no{@}=={@}"),
                "Required.",
                "procedures_" . $i
            );
            $this->addGroup(
                $group,
                "procedures_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        $this->addBasicText(
            "opening_pressure_mm",
            "Opening pressure (mm H2O): "
        );

        $this->addLabel("<h3>Sample collection</h3>");
        $this->addBasicText(
            "sampling_time",
            "Sampling time:"
        );
        $tubes = array(
                  "Total volume removed",
                  "Tube 1 Biochemistry",
                  "Tube 2 Microbiology",
                  "Tube 3",
                  "Tube 4",
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
            "mL"
        );
        $this->form->addGroup(
            $group,
            "sample_collection_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($tubes); $i++) {
            $group[] =& $this->createLabel($tubes[$i]);
            $group[] =& $this->createText(
                "tube_" . $i . "_volume",
                ""
            );
            $this->XINRegisterRule(
                "tube_" . $i . "_volume",
                array("tube_" . $i . "_volume{@}=={@}"),
                "Required.",
                "tube_" . $i
            );
            $this->addGroup(
                $group,
                "tube_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        $this->addSelect(
            "wash_of_antiseptics",
            "Wash of antiseptics:",
            $yesNoOptions
        );

        $this->addLabel("<h3>Complication</h3>");
        $complications = array(
                          "Traumatic puncture",
                          "Spinal nerve irritation",
                          "Headache",
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
        $this->form->addGroup(
            $group,
            "complications_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($complications); $i++) {
            $group[] =& $this->createLabel($complications[$i]);
            $group[] =& $this->createSelect(
                "complication_" . $i . "_yes_or_no",
                "",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "complication_" . $i . "_yes_or_no",
                array("complication_" . $i . "_yes_or_no{@}=={@}"),
                "Required.",
                "complication_" . $i
            );
            $this->addGroup(
                $group,
                "complications_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        $this->addLabel("<h3>Post lumbar puncture care</h3>");
        $postLumbarPunctureCare = array(
                                   "one hour rest",
                                   "Fluids",
                                   "Provide recommendations",
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
        $this->form->addGroup(
            $group,
            "post_lumbar_puncture_care_headers",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($postLumbarPunctureCare); $i++) {
            $group[] =& $this->createLabel($postLumbarPunctureCare[$i]);
            $group[] =& $this->createSelect(
                "post_lumbar_puncture_care_" . $i . "_yes_or_no",
                "",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "post_lumbar_puncture_care_" . $i . "_yes_or_no",
                array("post_lumbar_puncture_care_" . $i . "_yes_or_no{@}=={@}"),
                "Required.",
                "post_lumbar_puncture_care_" . $i
            );
            $this->addGroup(
                $group,
                "post_lumbar_puncture_care_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

    }
}

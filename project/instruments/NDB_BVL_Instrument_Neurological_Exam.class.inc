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
 * Creates the form elements for the Neurological Exam instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */

class NDB_BVL_Instrument_Neurological_Exam extends NDB_BVL_Instrument
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
        $this->form = new LorisForm('Neurological_Exam_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = 'Neurological_Exam';           // test_names.Test_name
        $this->table = 'Neurological_Exam';              // name of database table corresponding to instrument
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
            "/Neurological_Exam(_page[0-9]+)/",
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
        $this->addHeader("Neurological Exam");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();


    }

    function _page1() {
        $this->addHeader("Neurological Exam");

        /* CRANIAL NERVES */

        $this->addLabel("<h4>CRANIAL NERVES</h4>");

        $normalAbnormalOptions = array(
            null => "",
            1 => "1 - Normal",
            2 => "2 - Abnormal"
        );

        $cranialNervesNames = array(
            "II",
            "PERRAL",
            "Visual Fields",
            "III IV VI",
            "EOM's",
            "Nystagmus",
            "V",
            "VII",
            "VIII",
            "IX X",
            "XI",
            "XII"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Cranial Nerves"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Code"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Explain any abnormalities in the comments section."
        );
        $this->form->addGroup(
            $group,
            "cranial_nerves_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($cranialNervesNames); $i++) {
            $group[] =& $this->createLabel($cranialNervesNames[$i]);
            $group[] =& $this->createSelect(
                "cranial_nerves_" . $i . "_normal_or_abnormal",
                "cranial_nerves_normal_abnormal",
                $normalAbnormalOptions
            );
            $this->XINRegisterRule(
                "cranial_nerves_" . $i . "_normal_or_abnormal",
                array("cranial_nerves_" . $i . "_normal_or_abnormal{@}=={@}"),
                "Required.",
                "cranial_nerves_" . $i
            );
            $group[] =& $this->createText(
                "cranial_nerves_" . $i . "_comments",
                "cranial_nerves_comments"
            );
            $this->XINRegisterRule(
                "cranial_nerves_" . $i . "_comments",
                array("cranial_nerves_" . $i . "_normal_or_abnormal{@}=={@}2"),
                "Required if the answer is yes for this question.",
                "cranial_nerves_" . $i
            );
            $this->addGroup(
                $group,
                "cranial_nerves_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        /* MOTOR */

        $this->addLabel("<h4>MOTOR</h4>");
        $motorNames = array(
            "Arms: Proximal",
            "Arms: Distal",
            "Legs: Proximal",
            "Legs: Distal",
            "Tone",
            "Bulk"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Motor"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Code"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Explain any abnormalities in the comments section."
        );
        $this->form->addGroup(
            $group,
            "motor_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($motorNames); $i++) {
            $group[] =& $this->createLabel($motorNames[$i]);
            $group[] =& $this->createSelect(
                "motor_" . $i . "_normal_or_abnormal",
                "motor_normal_abnormal",
                $normalAbnormalOptions
            );
            $this->XINRegisterRule(
                "motor_" . $i . "_normal_or_abnormal",
                array("motor_" . $i . "_normal_or_abnormal{@}=={@}"),
                "Required.",
                "motor_" . $i
            );
            $group[] =& $this->createText(
                "motor_" . $i . "_comments",
                "motor_comments"
            );
            $this->XINRegisterRule(
                "motor_" . $i . "_comments",
                array("motor_" . $i . "_normal_or_abnormal{@}=={@}2"),
                "Required if the answer is yes for this question.",
                "motor_" . $i
            );
            $this->addGroup(
                $group,
                "motor_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }
    }

    function _page2() {
        $this->addHeader("Neurological Exam");

        $normalAbnormalOptions = array(
            null => "",
            1 => "1 - Normal",
            2 => "2 - Abnormal"
        );

        /* SENSORY */

        $this->addLabel("<h4>SENSORY</h4>");

        $sensoryNames = array(
            "Pinprick",
            "Fine touch",
            "Position",
            "Vibration"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Sensory"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Code"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Explain any abnormalities in the comments section."
        );
        $this->form->addGroup(
            $group,
            "cranial_nerves_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($sensoryNames); $i++) {
            $group[] =& $this->createLabel($sensoryNames[$i]);
            $group[] =& $this->createSelect(
                "sensory_" . $i . "_normal_or_abnormal",
                "sensory_normal_abnormal",
                $normalAbnormalOptions
            );
            $this->XINRegisterRule(
                "sensory_" . $i . "_normal_or_abnormal",
                array("sensory_" . $i . "_normal_or_abnormal{@}=={@}"),
                "Required.",
                "sensory_" . $i
            );
            $group[] =& $this->createText(
                "sensory_" . $i . "_comments",
                "sensory_comments"
            );
            $this->XINRegisterRule(
                "sensory_" . $i . "_comments",
                array("sensory_" . $i . "_normal_or_abnormal{@}=={@}2"),
                "Required if the answer is yes for this question.",
                "sensory_" . $i
            );
            $this->addGroup(
                $group,
                "sensory_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        /* CEREBELLAR*/

        $this->addLabel("<h4>CEREBELLAR</h4>");

        $cerebellarNames = array(
            "Finger to Nose",
            "Heel to Shin"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Cerebellar"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Code"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Explain any abnormalities in the comments section."
        );
        $this->form->addGroup(
            $group,
            "cerebellar_nerves_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($cerebellarNames); $i++) {
            $group[] =& $this->createLabel($cerebellarNames[$i]);
            $group[] =& $this->createSelect(
                "cerebellar_" . $i . "_normal_or_abnormal",
                "cerebellar_normal_abnormal",
                $normalAbnormalOptions
            );
            $this->XINRegisterRule(
                "cerebellar_" . $i . "_normal_or_abnormal",
                array("cerebellar_" . $i . "_normal_or_abnormal{@}=={@}"),
                "Required.",
                "cerebellar_" . $i
            );
            $group[] =& $this->createText(
                "cerebellar_" . $i . "_comments",
                "cerebellar_comments"
            );
            $this->XINRegisterRule(
                "cerebellar_" . $i . "_comments",
                array("cerebellar_" . $i . "_normal_or_abnormal{@}=={@}2"),
                "Required if the answer is yes for this question.",
                "cerebellar_" . $i
            );
            $this->addGroup(
                $group,
                "cerebellar_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        /* FRONTAL LOBE */

        $this->addLabel("<h4>FRONTAL LOBE</h4>");
        $frontalLobeNames = array(
            "Suck",
            "Snout",
            "Grasp",
            "Palmo Mental",
            "Glabellar"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Frontal Lobe"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Code"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Explain any abnormalities in the comments section."
        );
        $this->form->addGroup(
            $group,
            "frontal_lobe_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($frontalLobeNames); $i++) {
            $group[] =& $this->createLabel($frontalLobeNames[$i]);
            $group[] =& $this->createSelect(
                "frontal_lobe_" . $i . "_normal_or_abnormal",
                "frontal_lobe_normal_abnormal",
                $normalAbnormalOptions
            );
            $this->XINRegisterRule(
                "frontal_lobe_" . $i . "_normal_or_abnormal",
                array("frontal_lobe_" . $i . "_normal_or_abnormal{@}=={@}"),
                "Required.",
                "frontal_lobe_" . $i
            );
            $group[] =& $this->createText(
                "frontal_lobe_" . $i . "_comments",
                "frontal_lobe_comments"
            );
            $this->XINRegisterRule(
                "frontal_lobe_" . $i . "_comments",
                array("frontal_lobe_" . $i . "_normal_or_abnormal{@}=={@}2"),
                "Required if the answer is yes for this question.",
                "frontal_lobe_" . $i
            );
            $this->addGroup(
                $group,
                "frontal_lobe_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        /* GAIT */

        $this->addLabel("<h4>GAIT</h4>");
        $gaitNames = array(
            "Standard",
            "Tandom",
            "Rhomberg"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Gait"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Code"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Explain any abnormalities in the comments section."
        );
        $this->form->addGroup(
            $group,
            "gait_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($gaitNames); $i++) {
            $group[] =& $this->createLabel($gaitNames[$i]);
            $group[] =& $this->createSelect(
                "gait_" . $i . "_normal_or_abnormal",
                "gait_normal_abnormal",
                $normalAbnormalOptions
            );
            $this->XINRegisterRule(
                "gait_" . $i . "_normal_or_abnormal",
                array("gait_" . $i . "_normal_or_abnormal{@}=={@}"),
                "Required.",
                "gait_" . $i
            );
            $group[] =& $this->createText(
                "gait_" . $i . "_comments",
                "gait_comments"
            );
            $this->XINRegisterRule(
                "gait_" . $i . "_comments",
                array("gait_" . $i . "_normal_or_abnormal{@}=={@}2"),
                "Required if the answer is yes for this question.",
                "gait_" . $i
            );
            $this->addGroup(
                $group,
                "gait_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }
    }

    function _page3() {
        $this->addHeader("Neurological Exam");

        $codeScaleOptions = array(
            null => "",
            0 => "0 - Absent",
            1 => "1 - Decrease",
            2 => "2 - Normal",
            3 => "3 - Increase",
            4 => "4 - Hyperactive"
        );

        $section7names = array(
            "Biceps: Right",
            "Biceps: Left",
            "Triceps: Right",
            "Triceps: Left",
            "Brachio-radialis: Right",
            "Brachio-radialist: Left",
            "Knee: Right",
            "Knee: Left",
            "Ankle: Right",
            "Ankle: Left",
            "Plantar Response: Right",
            "Plantar Response: Left"
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
            "Code"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Explain any abnormalities in the comments section."
        );
        $this->form->addGroup(
            $group,
            "scale_group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($section7names); $i++) {
            $group[] =& $this->createLabel($section7names[$i]);
            $group[] =& $this->createSelect(
                "section7_" . $i . "_normal_or_abnormal",
                "section7_normal_abnormal",
                $codeScaleOptions
            );
            $this->XINRegisterRule(
                "section7_" . $i . "_normal_or_abnormal",
                array("section7_" . $i . "_normal_or_abnormal{@}=={@}"),
                "Required.",
                "section7_" . $i
            );
            $group[] =& $this->createText(
                "section7_" . $i . "_comments",
                "section7_comments"
            );
            $this->XINRegisterRule(
                "section7_" . $i . "_comments",
                array("section7_" . $i . "_normal_or_abnormal{@}=={@}2"),
                "Required if the answer is yes for this question.",
                "section7_" . $i
            );
            $this->addGroup(
                $group,
                "section7_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }
    }

    function _page4() {
        $this->addHeader("Neurological Exam");
        $this->addLabel("<h4>SUMMARY OF NEUROLOGICAL FINDINGS.</h4>");

        $yesNoOptions = array(
            null  => "",
            "yes" => "Yes",
            "no"  => "No",
        );

        $neurologicalFindings = array(
            "Cranial nerve functions",
            "Deep tendon reflexes (including Babinski)",
            "Motor examination, including muscle tone, tremor or cogwheeling",
            "Gait and station (including Romberg procedure)",
            "Primitive reflexes (snout, visual or tactile suck, grasp, glabellar Palmomental",
            "Sensorium",
            "Range or affect",
            "Expressive speech"
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
            "summary__group",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < count($neurologicalFindings); $i++) {
            $group[] =& $this->createLabel($neurologicalFindings[$i]);
            $group[] =& $this->createSelect(
                "summary_" . $i . "_abnormal",
                "summary_abnormal",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "summary_" . $i . "_abnormal",
                array("summary_" . $i . "_abnormal{@}=={@}"),
                "Required.",
                "summary_" . $i
            );
            $group[] =& $this->createText(
                "summary_" . $i . "_comments",
                "summary_comments"
            );
            $this->XINRegisterRule(
                "summary_" . $i . "_comments",
                array("summary_" . $i . "_abnormal{@}=={@}yes"),
                "Required if the answer is yes for this question.",
                "summary_" . $i
            );
            $this->addGroup(
                $group,
                "summary_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);

        }


    }


}

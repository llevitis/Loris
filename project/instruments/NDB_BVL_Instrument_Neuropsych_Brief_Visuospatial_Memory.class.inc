<?php
/**
 * This file contains the NDB_BVL_Instrument_Neuropsych_Brief_Visuospatial_Memory
 * class
 *
 * PHP Version 5
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Caitrin Armstrong <caitrin.armstrong@mail.mcgill.ca>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */
/**
 * Creates the form elements for the Brief Visuospatial Memory Instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Caitrin Armstrong <caitrin.armstrong@mail.mcgill.ca>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */
class NDB_BVL_Instrument_Neuropsych_Brief_Visuospatial_Memory extends NDB_BVL_Instrument_Additional_Options
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
        $this->form
            = new LorisForm('Neuropsych_Brief_Visuospatial_Memory_form');
        $this->page = $page;

        // set the object properties
        $this->testName = 'Neuropsych_Brief_Visuospatial_Memory';
        $this->table = 'Neuropsych_Brief_Visuospatial_Memory';
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
            'neuropsych_brief_visuospatial_learning_0',
            'neuropsych_brief_visuospatial_recognition_hit_11'
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
        if (preg_match(
            "/Neuropsych_Brief_Visuospatial_Memory(_page[0-9]+)/",
            $this->page, $matches
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
        $this->addHeader("Brief Visuospatial Memory Test - Revised");
        // for adding "Please indicate if: test not administered / test incomplete options
        $this->includeIncompleteOpts = true;

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();
        $score_columns
            = array(
                "trial_1_raw_score" => "(1) Trial 1/12",
                "trial_2_raw_score" => "(2) Trial 2/12",
                "trial_3_raw_score" => "(3) Trial 3/12",
                "total_recall_score" => "(4) Total recall/36",
                "learning_score" => "(5) Learning/12",
                "delayed_recall_score" => "(6) Delayed recall/12",
                "percent_retained_score" => "(7) Percent Retained/100",
                "recognition_hits_score" => "(8) Recognition hits/6",
                "recognition_false_alarms_score" => 
                    "(9) Recognition false alarms/6",
                "recognition_response_bias_score" => 
                    "(10) Recognition response bias/1",
                "recognition_discrimination_score" =>
                    "(11) Recognition discrimination/6",
                );
        while ($i = current($score_columns)) {
            $this->addScoreColumn(
                key($score_columns),
                $i
            );
            next($score_columns);
        }
        for ($i = 1; $i <= 6; $i++) {
            $this->addScoreColumn(
                "t_score_".$i,
                "(".($i+11).") t-score for (".$i.")"
            );
        }
        for ($i = 1; $i <= 11; $i++) {
            $this->addScoreColumn(
                "percentile_".$i,
                "(".($i+17).") percentile value for (".$i.")"
            );
        }
    }

    /**
     *Page 1
     *This Should really have numeric elements not selects, but I can't get them to
     *work in groups... could be easily changed to text inputs if half scores are
     * needed
     *
     * @return null
     **/
    function _page1()
    {

        $trials = array("Trial 1", "Trial 2", "Trial 3");
        $formOptions = array(
            null => "",
            1 => "1",
            2 => "2",
            3 => "3",
            4 => "4",
            5 => "5"
        );
        $trialScoreOptions = array(
            null => "",
            0 => "0",
            1 => "1",
            2 => "2",
            3 => "3",
            4 => "4",
            5 => "5",
            6 => "6",
            7 => "7",
            8 => "8",
            9 => "9",
            10 => "10",
            11 => "11",
            12 => "12"
        );

        // Header
        $this->addHeader("Brief Visuospatial Memory Test - Revised");
        $this->addlabel("<h4>Learning</h4>");

        NDB_BVL_Instrument::addSelect(
            "learning_form_administered",
            "Form Administered",
            $formOptions
        );

        $group[] = &$this->createLabel("Learning Trials");
        $group[] = &$this->createLabel("Raw Score");
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);


        for ($i = 0; $i < 3; $i++) {

            $trial = $trials[$i];

            $group[] = &$this->createLabel(
                "{$trial}."
            );

            $group[] =& $this->createSelect(
                "neuropsych_brief_visuospatial_learning_{$i}",
                "",
                $trialScoreOptions
            );

            $this->XINRegisterRule(
                "neuropsych_brief_visuospatial_learning_{$i}",
                array("neuropsych_brief_visuospatial_learning_{$i}{@}=={@}"),
                "Required.",
                "neuropsych_brief_visuospatial_learning_{$i}_group"
            );

            $this->form->addGroup(
                $group, "neuropsych_brief_visuospatial_learning_{$i}_group",
                null, $this->_GUIDelimiter, false
            );
            unset($group);
        }

        $this->addHourMinElement(
            "time_completed",
            "Time at which Trial 3 was completed:"
        );

        $this->dateTimeFields[] = "time_completed";

    }

    /**
     * Page 2
     *
     * @return null
     */
    function _page2()
    {
        $trials = array(
            "Delayed Recall",
            "Copy"
        );

        $formOptions = array(
            null => "",
            1 => "1",
            2 => "2",
            3 => "3",
            4 => "4",
            5 => "5"
        );

        $trialScoreOptions6 = array(
            null => "",
            0 => "0",
            1 => "1",
            2 => "2",
            3 => "3",
            4 => "4",
            5 => "5",
            6 => "6"
        );
        $trialScoreOptions12 = array(
            null => "",
            0 => "0",
            1 => "1",
            2 => "2",
            3 => "3",
            4 => "4",
            5 => "5",
            6 => "6",
            7 => "7",
            8 => "8",
            9 => "9",
            10 => "10",
            11 => "11",
            12 => "12"
        );

        $scoringPattern
            = [
            $trialScoreOptions12,
            $trialScoreOptions12
            ];
        // Header
        $this->addHeader("Brief Visuospatial Memory Test - Revised");
        $this->addLabel("<h4>Delayed Recall, Recognition, & Copy</h4>");
        $this->addHourMinElement(
            "time_delay_recall_start",
            "Time at which Delayed Recall started:"
        );
        $this->dateTimeFields[] = "time_delay_recall_start";
        $this->addNumericElement(
            "time_elapsed",
            "Time between Trial 3 and Delayed Recall (minutes)"
        );

        $this->addLabel(
            "Once the delayed recall, recognition and copy " .
            "trials have been completed and scored, " .
            "enter the values in the following table."
        );

        //note here I'm just adding time elapsed not time began,
        //because that's what Randi requested during QC for the
        //Screening visit for similar instruments
        NDB_BVL_Instrument::addSelect(
            "recal_recog_form_admin",
            "Form administered",
            $formOptions
        );

        $group[]
            = &$this->createLabel("Delayed Trials");
        $group[] = &$this->createLabel("Raw Score");
        $this->form->addGroup($group, null, null, $this->_GUIDelimiter, false);
        unset($group);

        for ($i = 0; $i < 2; $i++) {

            $trial = $trials[$i];
            $scoreOptions = $scoringPattern[$i];
            $group[] = &$this->createLabel("{$trial}");

            $group[] =& $this->createSelect(
                "neuropsych_brief_visuospatial_recall_{$i}",
                "",
                $scoreOptions
            );

            $this->XINRegisterRule(
                "neuropsych_brief_visuospatial_recall_{$i}",
                array("neuropsych_brief_visuospatial_recall_{$i}{@}=={@}"),
                "Required.",
                "neuropsych_brief_visuospatial_recall_{$i}_group"
            );

            $this->form->addGroup(
                $group, "neuropsych_brief_visuospatial_recall_{$i}_group",
                null, $this->_GUIDelimiter, false
            );
            unset($group);
        }

        //Recognition Trial Worksheet

        $falseAlarmYesNo = array(
            null => "",
            "yes" => "yes",
            "no"  => "NO"
        );

        $hitYesNo = array(
            null => "",
            "yes" => "YES",
            "no"  => "no"
        );

        $selectPatternHits = array(
            true, false, true, false,
            false, true, true, false,
            true, false, false, true
        );

        $selectPatternFalseAlarm = array(
            false, true, false, true,
            true, false, false, true,
            false, true, true, false
        );

        $trial_numbers = array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        $this->addLabel("Recognition Trial Worksheet");

        $group[] = &$this->createLabel("Item");
        $group[] = &$this->createLabel("Response");
        $this->form->addGroup(
            $group,
            null,
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        $group[] = &$this->createLabel("");
        $group[] = &$this->createLabel("Hits");
        $group[] = &$this->createLabel("False Alarms");

        $this->form->addGroup(
            $group,
            null,
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < 12; $i++) {

            $trial = $trial_numbers[$i];
            $group []= &$this->createLabel("{$trial}");

            if ($selectPatternHits[$i]) {
                $group[] =& $this->createSelect(
                    "neuropsych_brief_visuospatial_recognition_hit_{$i}",
                    "Hit",
                    $hitYesNo
                );

                $this->XINRegisterRule(
                    "neuropsych_brief_visuospatial_recognition_hit_{$i}",
                    ["neuropsych_brief_visuospatial_recognition_hit_{$i}{@}=={@}"],
                    "Required",
                    "neuropsych_brief_visuospatial_recognition_{$i}_group"
                );
            } else {
                $group[] = &$this->createLabel("");
            }

            if ($selectPatternFalseAlarm[$i]) {
                $group[] =& $this->createSelect(
                    "neuropsych_brief_visuospatial_recognition_false_{$i}",
                    "FalseAlarm",
                    $falseAlarmYesNo
                );

                $this->XINRegisterRule(
                    "neuropsych_brief_visuospatial_recognition_false_{$i}",
                    ["neuropsych_brief_visuospatial_recognition_false_{$i}{@}=={@}"],
                    "Required",
                    "neuropsych_brief_visuospatial_recognition_{$i}_group"
                );
            } else {
                $group[] = &$this->createLabel("");
            }


            $this->form->addGroup(
                $group, "neuropsych_brief_visuospatial_recognition_{$i}_group",
                null, $this->_GUIDelimiter, false
            );
            unset($group);
        }

    }
    /**
     * Scoring function
     * Sorry to whoever has to test this or even look at it (i.e. ted, probably)
     *
     * @return void
     */
    function score() 
    {
        if ($this->_determineDataEntryCompletionStatus() == "Incomplete") {
            return;
        }
        
        $db =& Database::singleton();
        //Get raw questions point values
        $query = "SELECT * FROM " . $this->table .
            " WHERE CommentID='" . $this->getCommentID() . "'";
        $record = $db->pselectRow($query, null);
        $candidate = Candidate::singleton($_REQUEST['candID']);
        $age_ary = Utility::calculateAge(
            $candidate->getCandidateDoB(),
            date('Y-m-d')
        );
        $age = $age_ary['year'];
        $score = array();
        // RAW SCORES
        $score["trial_1_raw_score"]
            = $record["neuropsych_brief_visuospatial_learning_0"];
        $score["trial_2_raw_score"]
            = $record["neuropsych_brief_visuospatial_learning_1"];
        $score["trial_3_raw_score"]
            = $record["neuropsych_brief_visuospatial_learning_2"];
        $score["total_recall_score"]
            = $score["trial_1_raw_score"]
            + $score["trial_2_raw_score"]
            + $score["trial_3_raw_score"];

        // LEARNING SCORE
        // Pick higher score between trial 2 and 3
        $higherVal
            = $score["trial_3_raw_score"] > $score["trial_2_raw_score"] ?
                $score["trial_3_raw_score"] : $score["trial_2_raw_score"];
        $score["learning_score"] = $higherVal - $score["trial_1_raw_score"];

        // DELAYED RECALL
        $score["delayed_recall_score"]
            = $record["neuropsych_brief_visuospatial_recall_0"];
        // PERCENT RETAINED
        $score["percent_retained_score"]
            = ($score["delayed_recall_score"] / $higherVal) * 100;
        // RECOGNITION HITS
        $selectPatternHits = array(
            true, false, true, false,
            false, true, true, false,
            true, false, false, true
        );
        $hitScore = 0;
        $faScore = 0;
        for($i = 0; $i < 12; $i++) {
            if ($selectPatternHits[$i]) {
                if($record["neuropsych_brief_visuospatial_recognition_hit_{$i}"] == "yes") {
                    $hitScore++;
                }
            }
            else {
                if($record["neuropsych_brief_visuospatial_recognition_false_{$i}"] == "yes") {
                    $faScore++;
                }
            }
        }
        $score["recognition_hits_score"] = $hitScore; 
        // RECOGNITION FALSE ALARMS
        $score["recognition_false_alarms_score"] = $faScore;
        // RECOGNITION RESPONSE BIAS
        $hits = $score["recognition_hits_score"];
        $falseAlarms = $score["recognition_false_alarms_score"];
        $query = "SELECT response_bias FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Response_Bias_Lookup WHERE ".
                "hits={$hits} AND false_alarms={$falseAlarms}";
        $score["recognition_response_bias_score"] = $db->pselectOne($query, array());
        // RECOGNITION DISCRIMINATION
        $score["recognition_discrimination_score"]
            = $score["recognition_hits_score"]
            - $score["recognition_false_alarms_score"];
        //==================== T-SCORES =====================
        // Trial 1 t-score
        $t1raw = $score["trial_1_raw_score"];
        $query = "SELECT t_score FROM ".
                        "Neuropsych_Brief_Visuospatial_Memory_Norms WHERE ".
                        "{$age} BETWEEN age_min and age_max AND ".
                        "trial_1={$t1raw}";
        $score["t_score_1"] = $db->pselectOne($query, array());

        // Trial 2 t-score
        $t2raw = $score["trial_2_raw_score"];
        $query = "SELECT t_score FROM ".
                        "Neuropsych_Brief_Visuospatial_Memory_Norms WHERE ".
                        "{$age} BETWEEN age_min and age_max AND ".
                        "trial_2={$t2raw}";
        $score["t_score_2"]  = $db->pselectOne($query, array());

        // Trial 3 t-score
        $t3raw = $score["trial_3_raw_score"];
        $query = "SELECT t_score FROM ".
                        "Neuropsych_Brief_Visuospatial_Memory_Norms WHERE ".
                        "{$age} BETWEEN age_min and age_max AND ".
                        "trial_3={$t3raw}";
        $score["t_score_3"] = $db->pselectOne($query, array());

        // Total Recall get your ass to mars t-score
        $trRaw = $score["total_recall_score"];
        $query = "SELECT t_score FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms WHERE ".
                "{$age} BETWEEN age_min and age_max AND ".
                "total_recall={$trRaw}";
        $score["t_score_4"] = $db->pselectOne($query, array());

        // Learning t-score
        $learningRaw = $score["learning_score"];
        $query = "SELECT t_score FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms WHERE ".
                "{$age} BETWEEN age_min and age_max AND ".
                "learning={$learningRaw}";
        $score["t_score_5"] = $db->pselectOne($query, array());

        // Delayed Recall t-score
        $delayedRaw = $score["delayed_recall_score"];
        $query = "SELECT t_score FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms WHERE ".
                "{$age} BETWEEN age_min and age_max AND ".
                "delayed_recall={$delayedRaw}";
        $score["t_score_6"] = $db->pselectOne($query, array());

        // ============= PERCENTILES ================
        // Trial 1 Percentile
        $query = "SELECT percentile FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms WHERE ".
                "{$age} BETWEEN age_min and age_max AND ".
                "trial_1={$t1raw}";
        $score["percentile_1"] = $db->pselectOne($query, array());

        // Trial 2 Percentile
        $query = "SELECT percentile FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms WHERE ".
                "{$age} BETWEEN age_min and age_max AND ".
                "trial_2={$t2raw}";
        $score["percentile_2"] = $db->pselectOne($query, array());

        // Trial 3 Percentile
        $query = "SELECT percentile FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms WHERE ".
                "{$age} BETWEEN age_min and age_max AND ".
                "trial_3={$t3raw}";
        $score["percentile_3"] = $db->pselectOne($query, array());

        // Total Recall percentile
        $query = "SELECT percentile FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms WHERE ".
                "{$age} BETWEEN age_min and age_max AND ".
                "total_recall={$trRaw}";
        $score["percentile_4"] = $db->pselectOne($query, array());

        // Learning percentile
        $query = "SELECT percentile FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms WHERE ".
                "{$age} BETWEEN age_min and age_max AND ".
                "learning={$learningRaw}";
        $score["percentile_5"] = $db->pselectOne($query, array());

        // Delayed Recall Percentile
        $query = "SELECT percentile FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms WHERE ".
                "{$age} BETWEEN age_min and age_max AND ".
                "delayed_recall={$delayedRaw}";
        $score["percentile_6"] = $db->pselectOne($query, array());

        // The following values are taken from the 2nd norms table
        // Percent Retained Percentile
        $prRaw = $score["percent_retained_score"];
        $query = "SELECT percentile FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms_2 WHERE ".
                "{$prRaw} BETWEEN percent_retained_min and percent_retained_max ".
                "AND {$age} BETWEEN age_min and age_max";
        $score["percentile_7"] = $db->pselectOne($query, array());

        // Recognition Hits Percentile
        $hitsRaw = $score["recognition_hits_score"];
        $query = "SELECT percentile FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms_2 WHERE ".
                "{$hitsRaw} BETWEEN hits_min and hits_max AND ".
                "{$age} BETWEEN age_min and age_max";
        $score["percentile_8"] = $db->pselectOne($query, array());

        // Recognition False Alarms Percentile
        $faRaw = $score["recognition_false_alarms_score"];
        $query = "SELECT percentile FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms_2 WHERE ".
                "{$faRaw} BETWEEN false_alarms_min and false_alarms_max AND ".
                "{$age} BETWEEN age_min and age_max";
        $score["percentile_9"] = $db->pselectOne($query, array());

        // Recognition Response Bias Percentile
        $rbRaw = $score["recognition_response_bias_score"];
        $query = "SELECT percentile FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms_2 WHERE ".
                "{$rbRaw} BETWEEN response_bias_min and response_bias_max ".
                "AND {$age} BETWEEN age_min and age_max";
        $score["percentile_10"] = $db->pselectOne($query, array());
        
        //Recognition Discrimination Index Percentile
        $diRaw = $score["recognition_discrimination_score"];
        $query = "SELECT percentile FROM ".
                "Neuropsych_Brief_Visuospatial_Memory_Norms_2 WHERE ".
                "{$diRaw} BETWEEN discrimination_index_min and ".
                "discrimination_index_max AND ".
                "{$age} BETWEEN age_min and age_max";
        $score["percentile_11"] = $db->pselectOne($query, array());
        $db->update(
            $this->table,
            $score,
            array('CommentID'=>$this->getCommentID())
        );
    }
}

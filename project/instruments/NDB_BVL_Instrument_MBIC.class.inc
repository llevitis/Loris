<?php
/**
 * This file contains the NDB_BVL_Instrument_MBIC
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
 * Creates the form elements for the MBIC instrument
 *
 * @category Instrument
 * @package  Neuropsych
 * @author   Liza Levitis <llevitis.mcin@gmail.com>
 * @license  http://www.gnu.org/licenses/gpl-3.0.txt GPLv3
 * @link     https://www.github.com/aces/CCNA/
 */
class NDB_BVL_Instrument_MBIC extends NDB_BVL_Instrument
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
    function setup($commentID, $page){
        $this->formType="XIN";
        $this->form = new LorisForm('MBIC_form');
        $this->page = $page;            // page label (number or
        // string - used by
        // user-defined child classes)

        // set the object properties
        $this->testName = 'MBIC';           // test_names.Test_name
        $this->table = 'MBIC';              // name of database table corresponding to instrument
        // data keyed by commentID
        $this->commentID = $commentID;

        //The array of dates/timestamps to convert to database dates/timestamps
        //Any HTML_Quickform date elements must be listed here
        $this->dateTimeFields=array("Date_taken");

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
        if (preg_match("/MBIC(_page[0-9]+)/",
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
        $this->addHeader("Mild Behavioral Impairment Checklist (MBI-C)");

        // automatically adds examiner & date of administration
        $this->_addMetadataFields();

        $score_columns
            = array(
            "total_score" => "Total score");
        while ($i = current($score_columns)) {
            $this->addScoreColumn(
                key($score_columns),
                $i
            );
            next($score_columns);
        }
    }

    function _page1(){

        $this->addHeader("Mild Behavioral Impairment Checklist (MBI-C)");

        $this->addLabel("This domain describes interest, motivation, and drive.");
        $yesNoOptions = array(
            null  => "",
            "yes" => "Yes",
            "no"  => "No"
        );

        $severityOptions = array(
            null => "",
            "1" => "1",
            "2" => "2",
            "3" => "3"
        );

        /* Interest, Motivation, and Drive Domain*/

        $IMD_questions = array(
            "Has the person lost interest in friends, family, or home activities?",
            "Does the person lack curiousity in topics that would usually have attracted her/his interest?",
            "Has the person become less spontaneous and active - for example, is she/he less likely
             to initiate or maintain conversation?",
            "Has the person lost the motivation to act on their obligations or interests?",
            "Is the person less affectionate and/or lacking in emotions when compared to her/his usual self?",
            "Does she/he no longer care about anything?"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Question"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Yes/No"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Severity"
        );
        $this->form->addGroup(
            $group,
            "interest_motivation_drive_domain",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < 6; $i++) {
            $group[] =& $this->createLabel($IMD_questions[$i]);
            $group[] =& $this->createSelect(
                "interest_motivation_drive_" . $i . "_yes_or_no",
                "Yes/No",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                  "interest_motivation_drive_" . $i . "_yes_or_no",
                  array("interest_motivation_drive_" . $i . "_yes_or_no{@}=={@}"),
                  "Required.",
                  "interest_motivation_drive_" . $i
            );
            $group[] =& $this->createSelect(
                "interest_motivation_drive_" . $i . "_severity",
                "Severity",
                $severityOptions
            );
            $this->XINRegisterRule(
                "interest_motivation_drive_" . $i . "_severity",
                array("interest_motivation_drive_" . $i . "_yes_or_no{@}=={@}yes"),
                "Required if the answer is yes for this question.",
                "interest_motivation_drive_" . $i
            );
            $this->addGroup(
                $group,
                "interest_motivation_drive_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        /* Mood or Anxiety Symptoms Domain */

        $this->addLabel("This domain describes mood or anxiety symptoms.");

        $MA_questions = array(
            "Has the person developed sadness or appear to be in low spirits? Does she/he
            have episodes of tearfulness?",
            "Has the person become less able to experience pleasure?",
            "Has the person become discouraged about their future or feel that she/he is a failure?",
            "Does the person view herself/himself as a burden to family?",
            "Has the person become more anxious or worried about things that are routine (e.g. events, visits, etc.)?",
            "Does the person feel very tense, having developed an inability to relax, or shakiness, or symptoms 
            of panic?"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Question"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Yes/No"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Severity"
        );
        $this->form->addGroup(
            $group,
            "mood_anxiety_domain",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < 6; $i++) {
            $group[] =& $this->createLabel($MA_questions[$i]);
            $group[] =& $this->createSelect(
                "mood_anxiety_" . $i . "_yes_or_no",
                "Yes/No",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "mood_anxiety_" . $i . "_yes_or_no",
                array("mood_anxiety_" . $i . "_yes_or_no{@}=={@}"),
                "Required.",
                "mood_anxiety_" . $i
            );
            $group[] =& $this->createSelect(
                "mood_anxiety_" . $i . "_severity",
                "Severity",
                $severityOptions
            );
            $this->XINRegisterRule(
                "mood_anxiety_" . $i . "_severity",
                array("mood_anxiety_" . $i . "_yes_or_no{@}=={@}yes"),
                "Required if the answer is yes for this question.",
                "mood_anxiety__" . $i
            );
            $this->addGroup(
                $group,
                "mood_anxiety_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        /* This domain describes the ability to delay gratification and control behavior,
        impulses, oral intake and/or changes in reward. */

        $this->addLabel("This domain describes the ability to delay gratification and control behavior, 
        impulses, oral intake and/or changes in reward.");

        $Delay_Control_questions = array(
            "Has the person become agitated, aggressive, irritable, or temperamental?",
            "Has she/he become unreasonably or uncharacteristically argumentative?",
            "Has the person become more impulsive, seeming to act without considering things?",
            "Does the person display sexually disinhibited or intrusive behaviour, such as touching (
            themselves/others), hugging, groping etc., in a manner that is out of character or may cause offence?",
            "Has the person become more easily frustrated or impatient? Does she/he have troubles coping 
            with delays, or waiting for events or for their turn?",
            "Does the person display a new recklessness or lack of judgment when driving (e.g. speeding, 
            erratic swerving, abrupt lane changes, etc.)?",
            "Has the person become more stubborn or rigid, i.e., uncharacteristically insistent on having their way, 
            or unwilling/unable to see/hear other views?",
            "Is there a change in eating behaviors (e.g. overeating, cramming the mouth, insistent 
            on eating only specific foods, or eating the food in exactly the same order)?",
            "Does the person no longer find food tasteful or enjoyable? Are they eating less?",
            "Does the person hoard objects when she/he did not do so before?",
            "Has the person developed simple repetitive behaviors or compulsions?",
            "Has the person recently developed trouble regulating smoking, alcohol, drug intake or gambling, 
            or started shoplifting?"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Question"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Yes/No"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Severity"
        );
        $this->form->addGroup(
            $group,
            "delay_control_domain",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < 12; $i++) {
            $group[] =& $this->createLabel($Delay_Control_questions[$i]);
            $group[] =& $this->createSelect(
                "delay_control_" . $i . "_yes_or_no",
                "Yes/No",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "delay_control_" . $i . "_yes_or_no",
                array("delay_control_" . $i . "_yes_or_no{@}=={@}"),
                "Required.",
                "delay_control_" . $i
            );
            $group[] =& $this->createSelect(
                "delay_control_" . $i . "_severity",
                "Severity",
                $severityOptions
            );
            $this->XINRegisterRule(
                "delay_control_" . $i . "_severity",
                array("delay_control_" . $i . "_yes_or_no{@}=={@}yes"),
                "Required if the answer is yes for this question.",
                "delay_control_" . $i
            );
            $this->addGroup(
                $group,
                "delay_control_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }
    }

    function _page2() {

        $this->addHeader("Mild Behavioral Impairment Checklist (MBI-C)");
        $yesNoOptions = array(
            null  => "",
            "yes" => "Yes",
            "no"  => "No"
        );
        $severityOptions = array(
            null => "",
            "1" => "1",
            "2" => "2",
            "3" => "3"
        );

        /* This domain describes following societal norms and having social graces, tact,
           and empathy. */

        $this->addLabel("This domain describes following societal norms and having social graces, tact,
           and empathy.");

        $Societal_Social_questions = array(
            "Has the person become less concerned about how her/his words or actions affect others? Has she/he
            become insensitive to others' feelings?",
            "Has the person started talking openly about very personal or private matters not usually 
            discussed in public?",
            "Does the person say rude or crude things or make lewd sexual remarks that she/he would
            not have said before?",
            "Does the person seem to lack judgement she/he previously had about what to say or
            how to behave in public or private?",
            "Does the person now talk to strangers as if familiar, or intrude on their activities?"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Question"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Yes/No"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Severity"
        );
        $this->form->addGroup(
            $group,
            "societal_social_domain",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);


        for ($i = 0; $i < 5; $i++) {
            $group[] =& $this->createLabel($Societal_Social_questions[$i]);
            $group[] =& $this->createSelect(
                "societal_social_" . $i . "_yes_or_no",
                "Yes/No",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "societal_social_" . $i . "_yes_or_no",
                array("societal_social_" . $i . "_yes_or_no{@}=={@}"),
                "Required.",
                "societal_social_" . $i
            );
            $group[] =& $this->createSelect(
                "societal_social_" . $i . "_severity",
                "Severity",
                $severityOptions
            );
            $this->XINRegisterRule(
                "societal_social_" . $i . "_severity",
                array("societal_social_" . $i . "_yes_or_no{@}=={@}yes"),
                "Required if the answer is yes for this question.",
                "societal_social_" . $i
            );
            $this->addGroup(
                $group,
                "societal_social_" . $i,
                null,
                $this->_GUIDelimiter,
                false
            );
            unset($group);
        }

        /* This domain describes strongly held beliefs and sensory experiences. */

        $this->addLabel("This domain describes strongly held beliefs and sensory experiences.");

        $Beliefs_Sensory_questions = array(
            "Has the person developed beliefs that they are in danger, or that others are planning
            to harm them or steal their belongings?",
            "Has the person developed suspiciousness about the intentions or motives of other people?",
            "Does she/he have unrealistic beliefs about her/his power, wealth, or skills?",
            "Does the person describe hearing voices or does she/he talk to imaginary people or 'spirits'?",
            "Does the person report or complain about, or act as if seeing things (e.g. people, 
            animals, or insects) that are not there, i.e., that are imaginary to others?"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Question"
        );

        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Yes/No"
        );
        $group[] =& $this->form->createElement(
            "static",
            null,
            null,
            "Severity"
        );
        $this->form->addGroup(
            $group,
            "beliefs_sensory_domain",
            null,
            $this->_GUIDelimiter,
            false
        );
        unset($group);

        for ($i = 0; $i < 5; $i++) {
            $group[] =& $this->createLabel($Beliefs_Sensory_questions[$i]);
            $group[] =& $this->createSelect(
                "beliefs_sensory_" . $i . "_yes_or_no",
                "Yes/No",
                $yesNoOptions
            );
            $this->XINRegisterRule(
                "beliefs_sensory_" . $i . "_yes_or_no",
                array("beliefs_sensory_" . $i . "_yes_or_no{@}=={@}"),
                "Required.",
                "beliefs_sensory_" . $i
            );
            $group[] =& $this->createSelect(
                "beliefs_sensory_" . $i . "_severity",
                "Severity",
                $severityOptions
            );
            $this->XINRegisterRule(
                "beliefs_sensory_" . $i . "_severity",
                array("beliefs_sensory_" . $i . "_yes_or_no{@}=={@}yes"),
                "Required if the answer is yes for this question.",
                "beliefs_sensory_" . $i
            );
            $this->addGroup(
                $group,
                "beliefs_sensory_" . $i,
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

        $score[total_score] = 0;
        /* add up domain #1 score */
        for ($i = 0; $i < 6; $i++) {
            $score[total_score] += $record["interest_motivation_drive_" . $i . "_severity"];
        }
        /* add up domain #2 score */
        for ($i = 0; $i < 6; $i++) {
            $score[total_score] += $record["mood_anxiety_" . $i . "_severity"];
        }
        /* add up domain #3 score */
        for ($i = 0; $i < 12; $i++) {
            $score[total_score] += $record["delay_control_" . $i . "_severity"];
        }
        /* add up domain #4 score */
        for ($i = 0; $i < 5; $i++) {
            $score[total_score] += $record["societal_social_" . $i . "_severity"];
        }
        for ($i = 0; $i < 5; $i++) {
            $score[total_score] += $record["beliefs_sensory_" . $i . "_severity"];
        }

        $db->update(
            $this->table,
            $score,
            array('CommentID'=>$this->getCommentID())
        );
    }

}
?>

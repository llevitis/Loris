/*global document: false, $: false, window: false, unescape: false, Option: false,isElementsSet, alert*/
<<<<<<< 3a82da2167300510bdffb3fc9a433e97ade0ee28
=======

loris.hiddenHeaders = ['Consent To Study'];

function checkAccessProfileForm() {
    'use strict';
    var form = document.accessProfileForm;
    if (form.candID.value === "") {
        alert("You must enter a DCC-ID");
        form.candID.focus();
        return false;
    }
    if (form.PSCID.value === "") {
        alert("You must enter a PSCID");
        form.PSCID.focus();
        return false;
    }

    $.get(loris.BaseURL + "/AjaxHelper.php?Module=candidate_list&script=validateProfileIDs.php&candID=" + form.candID.value + "&PSCID=" + form.PSCID.value ,
        function(data)
        {
            //ids are valid, submit accessProfileForm form
            if (data==1) {
                $( "#accessProfileForm" ).unbind('submit.formValidation');
                form.submit();
            }
            else {
                //display error message

                alert("DCCID or PSCID is not valid");
            }
        }
    );

    return false;
}

>>>>>>> working on modifying the appearance of consent for study_consent being set to no
function hideFilter(obj) {
    'use strict';

     var heading = $(obj);
     var arrow   = $(obj).children('.arrow');
     if (heading.hasClass('panel-collapsed')) {
            // expand the panel
            heading.parents('.panel').find('.panel-body').slideDown();
            heading.removeClass('panel-collapsed');
            arrow.removeClass('glyphicon-chevron-down').addClass('glyphicon-chevron-up');
        } else {
            // collapse the panel
            heading.parents('.panel').find('.panel-body').slideUp();
            heading.addClass('panel-collapsed');
            arrow.removeClass('glyphicon-chevron-up').addClass('glyphicon-chevron-down');
        }
}
function toggleMe() {
    "use strict";
    $("#advanced-label").toggle();
    $(".advancedOptions").toggle();
    $(".advanced-buttons").toggle();
}


$(function(){
        $('input[name=dob]').datepicker({
            dateFormat: 'yy-mm-dd',
            changeMonth: true,
            changeYear: true
        });
});

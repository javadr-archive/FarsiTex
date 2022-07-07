
/**
* Enable or disable all elements inside div
*
*/
function setDivEnabled(divElm, enabled){
    if(enabled==null) {
        alert("Please call this function with two parameters");
    }
    if (enabled) {
        jQuery(divElm).removeClass("disabled");
        jQuery(divElm).find("input").attr('disabled','');
    } else {
        jQuery(divElm).addClass("disabled");
        jQuery(divElm).find("input").attr('disabled','disabled');
    }
}

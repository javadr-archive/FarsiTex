function initDurationInput(){
    setDurationVisibility();
    $("input[@id='durationSelectedFalse']").click(setDurationVisibility);
    $("input[@id='durationSelectedTrue']").click(setDurationVisibility);
}

function setDurationVisibility(){
    if (document.getElementById('durationSelectedTrue').checked) {
        $("input[@id='durationAsString']").show().css("display", "inline");
    } else if(document.getElementById('durationSelectedFalse').checked){
        $("input[@id='durationAsString']").hide();
    }
}

function changePageLimit(location, selectElm) {
    var loc = new LocationModifier(location);
    loc.setParam("limit", selectElm.options[selectElm.selectedIndex].value);
    location.href = loc.getLocation();
}


var SfTable = function(tableId) {
    //ctor
    this.tableId = tableId;
};

SfTable.prototype = {
    initialize: function() {
        jQuery('.description').find('.desc_right').truncate(512);

        jQuery('#detailsToggle').addClass('link').toggle(this._showDetails.bind(this), this._hideDetails.bind(this));

        if (jQuery('#detailsToggle').attr('class') != null && jQuery('#detailsToggle').attr('class').indexOf('sel') >= 0) {
            jQuery('#detailsToggle').click();
        }

        if (this.getDetailsVisibilitySetting() != this.detailsAreVisible()) {
            this.clickDetailsToggle();
        }
    },

    _showDetails: function() {
        jQuery('#detailsToggle').addClass('sel');
        jQuery('.description').find('.hide').show().css('height', '100%');
        this.setDetailsVisibilitySetting(true);
    },

    _hideDetails: function() {
        jQuery('#detailsToggle').removeClass('sel');
        jQuery('.description').find('.hide').hide();
        this.setDetailsVisibilitySetting(false);
    },

    clickDetailsToggle: function () {
        jQuery('#detailsToggle').click();
    },

    setDetailsVisibilitySetting: function(isVisible) {
        document.setCookie("sfTable_" + this.tableId + "_detailsAreVisible", isVisible ? "true" : "false");
    },

    getDetailsVisibilitySetting: function() {
        return document.getCookie("sfTable_" + this.tableId + "_detailsAreVisible") == "true";
    },

    detailsAreVisible: function () {
        return document.getElementById('detailsToggle').className == "link sel";
    }
}

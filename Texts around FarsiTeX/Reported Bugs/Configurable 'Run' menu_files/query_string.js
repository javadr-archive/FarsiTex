function QueryString(qs) {
    this.params = new Array();
    this.setQueryString = function(queryString) {
        if (queryString != null && queryString != "") {
            //remove the ?
            queryString = queryString.split("?")[1];
            //split into array of parms
            var tmpParams = queryString.split("&");
            if (tmpParams.length > 0 && tmpParams[0] != "") {
                for (var i = 0; i < tmpParams.length; i++) {
                    this.params[i] = tmpParams[i].split("=");

                }
            }
        }
    }
    this.setQueryString(qs);
    this.getQueryString = function() {
        var returnStr = "";
        if (this.params.length > 0) {
            returnStr += "?";

            for (var i = 0; i < this.params.length; i++) {
                if (i > 0) {
                    returnStr += "&";
                }
                returnStr += this.params[i].join("=");
            }
        }
        return returnStr;
    }
    this.setParam = function (name, value) {
        var found = false
        for (var i = 0; i < this.params.length; i++) {
            if (!found && this.params[i][0] == name) {
                found = true;
                this.params[i][1] = value;
            }
        }
        if (!found) {
            this.params.push(new Array(name, value));
        }
    }
}

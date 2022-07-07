function LocationModifier(location) {
    this.location = location;
    this.queryString = new QueryString(location.search);
    this.setParam = function(name, value) {
        this.queryString.setParam(name, value);
    }
    this.getLocation = function() {
        var theLocation = "";
        if (this.location.href.lastIndexOf("?") == this.location.href.length - 1) {
            theLocation = this.location.href.substring(0, this.location.href.length - 1);
        } else {
            theLocation = this.location.href.substring(0, this.location.href.length - this.location.search.length);
        }
        return theLocation + this.queryString.getQueryString();
    }
}
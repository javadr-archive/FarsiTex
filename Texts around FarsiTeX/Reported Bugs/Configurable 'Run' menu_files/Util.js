// from http://blog.reindel.com/2007/03/14/the-truncate-plugin-for-jquery/
jQuery.fn.truncate = function(max,settings) {
    settings = jQuery.extend({
        chars: /\s/,
        trail: "..."
    }, settings);
    return this.each(function(){
        v = jQuery.trim(jQuery(this).text());
        if (v.length > max) {
            while (max > 0) {
                c = v.charAt(max);
                if (c.match(settings.chars)) {
                    jQuery(this).html(v.substring(0,max) + settings.trail);
                    break;
                }
                max--;
            }
        }
    });
};


String.prototype.trim = function() {
    return this.replace(/^\s+|\s+$/g, "");
}


// adapted from http://www.quirksmode.org/js/cookies.html
document.setCookie = function(name, value, days) {
    var expires = "";
    if (days) {
        var date = new Date();
        date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
        expires = "; expires=" + date.toGMTString();
    }
    this.cookie = name + "=" + value + expires + "; path=/";
}

document.getCookie = function(name) {
    var nameEQ = name + "=";
    var ca = this.cookie.split(';');
    for (var i = 0; i < ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0) == ' ') c = c.substring(1, c.length);
        if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length, c.length);
    }
    return null;
}

document.clearCookie = function(name) {
    this.setCookie(name, "", -1);
}

// from prototype 1.5.0
var $A = Array.from = function(iterable) {
    if (!iterable) return [];
    if (iterable.toArray) {
        return iterable.toArray();
    } else {
        var results = [];
        for (var i = 0, length = iterable.length; i < length; i++)
            results.push(iterable[i]);
        return results;
    }
}
Function.prototype.bind = function() {
    var __method = this, args = $A(arguments), object = args.shift();
    return function() {
        return __method.apply(object, args.concat($A(arguments)));
    }
}

/*
 * Licensed under the MIT License:
 *   http://www.opensource.org/licenses/mit-license.php
 * This collection of scripts is built on top of the very light weight jQuery library.
 * Credit for jquery menu goes to Myles Angell with a bit of shim correction from Adam Cooper
 */

function SfGoods() {
}

SfGoods.prototype.constructor = function(){
    this.initFormNoteBehavior();
    this.toggleCheckboxInfo()
}

SfGoods.prototype.toggleCheckboxInfo = function(){
	if (jQuery(this).is(":checked"))
	    {jQuery(this).parent('label').parent('p').next('div').addClass('info').show();}
    else
        {jQuery(this).parent('label').parent('p').next('div.info').hide();}
}

SfGoods.prototype.initFormNoteBehavior = function() {
    jQuery("form .note").focus(function() {
        jQuery(this).parent('p').addClass('helptip').removeClass('hide').addClass('show');
        jQuery(this).prev('small').removeClass('hide').addClass('show');
    });
    jQuery("form .note").blur(function() {
        jQuery(this).parent('p').removeClass('helptip');
        jQuery(this).prev('small').removeClass('show').addClass('hide');
    });
    jQuery("form .notemulti").focus(function(){
        jQuery(this).parent('p').parent('div').addClass('helptip').removeClass('hide').addClass('show');
        jQuery(this).prev('small').removeClass('hide').addClass('show');
    });
    jQuery("form .notemulti").blur(function(){
        jQuery(this).parent('p').parent('div').removeClass('helptip');
        jQuery(this).prev('small').removeClass('show').addClass('hide');
    });
}

jQuery(document).ready(function(){
    var sfGoods = new SfGoods();
    sfGoods.initFormNoteBehavior();
    jQuery("div.firstwave li").hoverClass("sfHover");
    jQuery(".tools").prepend("<div></div><span>Tools</span>");
    jQuery(".toolsadmin").prepend("<div></div><span>Project Admin</span>");
    jQuery(".subdiv").prepend("<div></div><span>&nbsp;</span>");
	jQuery("select").change(function(){
		if (jQuery(this).find("option[@value='0']").is(":selected"))
			{ jQuery(this).next('textarea').removeClass('hide'); }
		else
			{ jQuery(this).next('textarea').addClass('hide'); }
	});
        jQuery("p label input[@type='checkbox']").each(sfGoods.toggleCheckboxInfo);
        jQuery("p label input[@type='checkbox']").change(sfGoods.toggleCheckboxInfo);


        jQuery('label').click(function(){
		if (jQuery(this).find("input[@type='radio']").attr("checked","yes"))
			{jQuery("input[@type='radio']").parent('label').parent('p').next('div.info').hide(); jQuery(this).parent('p').next('div').addClass('info').show();}
		else
        		{jQuery(this).parent('p').next('div.info').hide();}
	});

	jQuery(".actionb").mousedown(function(){jQuery(this).addClass("actionbc");});
	jQuery(".actionb").mouseup(function(){jQuery(this).removeClass("actionbc");});

	jQuery("input[@disabled='disabled']").css("color","#000");
	jQuery('.toggle').prepend('<span class="collapse">&nbsp;</span>');
	jQuery('.toggle span').toggle(function(){
		jQuery(this).removeClass('collapse').addClass('expand').parent('.toggle').next('div').css("width","auto").toggle('fast');
          },function(){
		jQuery(this).removeClass('expand').addClass('collapse').parent('.toggle').next('div').toggle('fast');
          });
        jQuery('.togglebasic').click(function(){ jQuery(this).next('span').toggle('fast');});

	jQuery('table.notifications td.project').addClass('link');
    jQuery('table#searchtable td').click(function(){if (jQuery(this).is(".project") || jQuery(this).is(".select")){}else{jQuery(this).parent('tr').next('tr td').find('.hide').css('height','100%').toggle('fast');};});

	jQuery('#detail').addClass('link').toggle(
		function(){
			jQuery(this).addClass('sel');
			jQuery('.description').find('.show').hide();
			jQuery('.description').find('.hide').show().css('height','100%');
            jQuery('.description').find('ul li').show();
        }
		,function(){
			jQuery(this).removeClass('sel');
			jQuery('.description').find('.hide').hide();
            jQuery('.description').find('.show').show();
            jQuery('.description').find('ul li:gt(2)').hide();
        }
    );
    if( jQuery('#detail').attr('class') != null && jQuery('#detail').attr('class').indexOf('sel') >= 0 ) {
        jQuery('#detail').click();
    }

        jQuery('#images').addClass('link').toggle(
                function(){
                        jQuery(this).addClass('sel');
                        jQuery('.ssimage').hide();}
                ,function(){
                        jQuery(this).removeClass('sel');
                        jQuery('.ssimage').show();
                        });
	jQuery('table.notifications td.project a').click(function(){jQuery(this).parent('strong').parent('td').parent('tr').find('.newitem').removeClass('newitem').addClass('read').css('font-weight','normal'); jQuery(this).parent('strong').css('font-weight','normal');});
 	jQuery('table.notifications td.project a').click(function(){jQuery(this).parent('td').parent('tr').find('.unread').removeClass('unread').addClass('read').css('font-weight','normal');});
	jQuery("#password input").keyup(function(){ if (this.value.length < 6) {jQuery('#verify').remove(); jQuery(this).next('input').after('<span id="verify"> Too Short</span>');} else {jQuery('#verify').remove(); jQuery(this).next('input').after('<span id="verify"> Good</span>');}});
	jQuery('.required').append('<b title="Required">*</b>');
});
jQuery.fn.hoverClass = function(c) {
        return this.each(function(){
                jQuery(this).hover(
                        function() { jQuery(this).addClass(c); },
                        function() { jQuery(this).removeClass(c); }
                );
        });
};
jQuery.fn.setFocus = function(e){
    if (document.getElementById(e)) document.getElementById(e).focus();
    return this;
};
// function to break up project nav submenu items which have too many characters
cleanProjNavItems = function() {
        // for each of the "firstwave ul li a" elements ...
        jQuery(".firstwave ul ul li a").each(function(){
                // wordWrap the contents and re-assign
                jQuery(this).html(wordWrap(jQuery(this).text(), 20, " ", true));
        });
};
// wordWrap function adapted from http://www.bigbold.com/snippets/posts/show/869
wordWrap = function(bigString, m, b, c){
    var i, j, s, r = bigString.split(" ");
    if(m > 0) for(i in r){
        for(s = r[i], r[i] = ""; s.length > m;
            j = c ? m : (j = s.substr(0, m).match(/\S*$/)).input.length - j[0].length
            || m,
            r[i] += s.substr(0, j) + ((s = s.substr(j)).length ? b : "")
        );
        r[i] += s;
    }
    return r.join(" ");
};
jQuery(document).ready(cleanProjNavItems);
// function for re-sizing each of the firstwave ul\'s in case they go beyond the visible browser window
resizeNavDropdowns = function(){
        // for every "firstwave ul" element ...
        jQuery("#frame div.firstwave ul").each(function(){
                // if the element\'s y position + height is more than the browser window height
                if(jQuery(this).height() + 255 > TB_getPageSize()[1]){
                        // reset the height of this element to be the browser window height, minus all the SF.net top banner overhead
                        jQuery(this).height((TB_getPageSize()[1] - 340) + "px");
                        // set overflow:auto to the element to enable the scroll bar
                        jQuery(this).css("overflow","auto").addClass("flow");
                }
         });
};

jQuery(document).ready(resizeNavDropdowns);

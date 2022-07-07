/*
 * Licensed under the MIT License:
 *   http://www.opensource.org/licenses/mit-license.php
 * This collection of scripts is built on top of the very light weight jQuery library.
 */
function escapeHtml(s) {
    string = new String(s)
    string = string.replace(/&/g,"&amp;");
    string = string.replace(/"/g,"&quot;");
    string = string.replace(/</g,"&lt;");
    string = string.replace(/>/g,"&gt;");
    return string;
}

jQuery(document).ready(function(){
    var sfGoods = new SfGoods();
        jQuery("input.currency").click(function(){
                jQuery("input.amt").hide().css("display","none");
                jQuery(this).next('input').show().css("display", "inline");
        });

	jQuery("input.yea").click(function(){
		jQuery("div.right").show();
                jQuery("div.searchpro").show();
		jQuery("div.special").hide();
	  });
	jQuery("input.yes1").click(function(){jQuery(this).next('select').show().css("display","inline");jQuery('p.servproject').hide();jQuery('div.right').hide();jQuery('div.special').hide();});
	jQuery("input.no1").click(function(){jQuery(this).prev('br').prev('select').hide();jQuery('p.servproject').show();jQuery('div.servicetype').hide();});
	jQuery("input.nay").click(function(){
		jQuery("div.right").show();
		jQuery("div.searchpro").hide();
		jQuery("div.searchthis").hide();
		jQuery("div.special").show();
		jQuery("span.cat_area").html("2.");
	  });
	jQuery("input.sel01").click(function(){
		jQuery("div.special").show();
		jQuery(".searchpro .message").show();
		jQuery("div.searchthis").hide();
	  });
	jQuery("input.search1").click(function(){jQuery("div.searchthis").show();});
	jQuery("option[@value='nolimit']").click(function(){jQuery(this).parent('select').next('input').hide();});
        jQuery("option[@value='other']").click(function(){jQuery(this).parent('select').next('textarea').show();});
	jQuery("option[@value='proj1']").click(function(){jQuery("div.servicetype").show();});
	jQuery("input[@value='days']").click(function(){jQuery(this).next('input').show().css("display", "inline");});
	jQuery("input[@value='days0']").click(function(){jQuery(this).next('br').next('input').next('input').hide();});
	jQuery("input.service3").click(function(){jQuery("div.right").show();jQuery("div.searchpro").hide();jQuery("div.special").show();});
	jQuery("input.service3a").click(function(){jQuery("div.right").show();});
	jQuery('.printme').html('<a href="javascript:window.print()" class="print">Printable version</a>');
	jQuery('select.serviceContract').change(function(){
		jQuery('input.serviceContractTitle').val(jQuery('select.serviceContract option:selected').text());
		jQuery('input.serviceContractFilename').val(jQuery('select.serviceContract option:selected').val());
	});
	jQuery('textarea.note').change(function(){
		jQuery("#desc_preview").empty();
		jQuery("#desc_preview").append("<pre id='previewText' class='wordwrapped'>"+escapeHtml(jQuery(this).val())+"</pre>");
	});
	jQuery('input[@name=currency]').click(function(){
        jQuery('input[@name=totalPrice]').css("display", "inline");
        jQuery('input[@name=totalPrice]').insertAfter(this);
    });
    jQuery('input[@name=totalPrice]').focus(function() {
        jQuery('small[@id=totalPrice_hint3]').show().removeClass('hide').addClass('show');
    });
    jQuery('input[@name=totalPrice]').blur(function() {
        jQuery('small[@id=totalPrice_hint3]').hide().removeClass('show').addClass('hide');
    });
});
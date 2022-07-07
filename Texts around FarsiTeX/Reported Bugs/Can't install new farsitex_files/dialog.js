function TD_show(params,callback) {

	defaults = {
		msg: 'Are you sure?',
		width: 200,
		height: 50,
		ok: 'OK',
		cancel: 'Cancel'
	}
	if(params) defaults = jQuery.extend(defaults,params);

	if (typeof callback != 'function') {
		follow = callback.href;
		callback = function() { location.href = follow; }
	}

	try {
		
		if (document.getElementById("TB_HideSelect") == null) {
			jQuery("body").append("<iframe id='TB_HideSelect'></iframe><div id='TB_overlay'></div><div id='TB_window'></div>");
		}

		jQuery(window).scroll(TB_position);
		TB_overlaySize();
			
		TB_WIDTH = (defaults.width*1) + 30;
		TB_HEIGHT = (defaults.height*1) + 40;
		ajaxContentW = TB_WIDTH - 40;
		ajaxContentH = TB_HEIGHT - 40;

		jQuery("#TB_window").append("<div id='TB_ajaxContent'>"+defaults.msg+"<div id='TB_dialogButtons'><a href='#' id='TD_okButton' class='ok'>"+defaults.ok+"</a> <a href='#' id='TD_cancelButton' class='cancel'>"+defaults.cancel+"</a></div></div>");
		if (defaults.classname) jQuery("#TB_window").addClass(defaults.classname);
		jQuery("#TB_ajaxContent").css({'padding': '20px', 'width': ajaxContentW+'px'});
		
		jQuery("#TD_okButton").click(function() { 
										 	TD_remove();
											callback();
											return false;
											});
		jQuery("#TD_cancelButton").click(function() { 
										 	TD_remove();
											return false;
											});
			
		TB_position();
		jQuery("#TB_window").css({display:"block"}); 
		
		jQuery(window).resize(TB_position);
		
		// close on escape
		document.onkeyup = function(e){ 	
			if (e == null) { // ie
				keycode = event.keyCode;
			} else { // mozilla
				keycode = e.which;
			}
			if(keycode == 27){ // close
				TB_remove();
				return false;
			}	
		}

	} catch(e) {
		console.warn( e );
	}
	
	return false;
}

//helper functions below
function TD_remove() {
	jQuery("#TB_window").fadeOut("fast",function(){jQuery('#TB_window,#TB_overlay,#TB_HideSelect').remove();});
}

google_encoding = 'utf8';
google_ad_section = 'default';
google_image_size = '728x90';

if (window.hint) { google_hints = window.hint; }
if (!window.google_safe) { google_safe = 'high'; }
if (!window.google_max_num_ads) { google_max_num_ads = '3'; }
if (!window.google_ad_output) { google_ad_output = 'js'; }
if (!window.google_feedback) { google_feedback = 'on'; }
if (!window.ostg_ad_leader_width) { ostg_ad_leader_width  = '728'; }
if (!window.ostg_ad_leader_height) { ostg_ad_leader_height  = '90'; }
if (!window.ostg_style_type) { ostg_style_type = 'standard'; }

if (!window.google_ad_format) { google_ad_format = google_image_size + '_pas_abgnc'; } 

// If IMU ads were already requested
if ((typeof imu_ads != 'undefined') && (window.imu_ads.length < 1 )) {
	if (window.imu_ads[0].type != 'text') {
		google_ad_type = 'text';
		google_image_size = '';
	}
}

// google_oasu_url = 'http://ad.doubleclick.net/clk;39821406;13502407;y?https://adwords.google.com/select/OnsiteSignupLandingPage?client=ca-ostg_js&referringUrl=sourceforge.net';

currWin = window;
while (currWin.parent != currWin) {
	   currWin = currWin.parent;
}

// Redirects Google Bot to different pages for content matching
full_url = ""+currWin.location;
if (!window.google_page_url) {
	google_page_url = ""+full_url;
	if (full_url.match(/slashdot/)) {
		google_ad_section = 'apple askslashdot backslash books developers games hardware interviews it linux politics science yro default';
	}
	if (full_url.match(/project\/showfiles\.php\?group_id=(\d+)/)) {
		google_page_url = 'http://sourceforge.net/project/?group_id=' + RegExp.$1;
	}
        if (full_url.match(/project\/downloading\.php\?group_id=(\d+)/)) {
                google_page_url = 'http://sourceforge.net/project/?group_id=' + RegExp.$1;
        }
	if (window.slashdot_article_url) {
		google_page_url = slashdot_article_url;
	}
	if (window.sf_proj_home) { google_page_url = sf_proj_home; }
}


function google_ad_request_done(google_ads) {

	// Proceed only if we have ads to display! 
	if (google_ads.length < 1 ) return;

	if (ostg_style_type == 'multi_hilite') {

		ostg_google_style = 'font-family: arial, sans-serif; color: #555; overflow: hidden; font-size: 12px; padding: 0;';
		ostg_ga_style = 'font-size: 10px; text-align: center; line-height: 12px;';
		ostg_ga_link = 'color: #ccc;';
		ostg_ad_leader = 'padding: 5px; margin-right: 5px; float: left; width: 225px; height: 70px; border: 1px solid #fc3; background: #ffe;';
		ostg_ad_title = 'color: #800; font-weight: bold; font-size: 13px;';
		ostg_ad_url = 'color: #888; font-size: 11px;';

		ostg_ad_leader_extra = ['padding: 5px; margin-right: 5px; float: left; width: 225px; height: 70px; border: 1px solid #fc3; background: #ffe;',
					'padding: 5px; margin-right: 5px; float: left; width: 225px; height: 70px; border: 1px solid #fc3; background: #ffe;',
					'padding: 5px; margin-right: 5px; float: left; width: 225px; height: 70px; border: 1px solid #fc3; background: #ffe;',
					'padding: 5px; margin-right: 5px; float: left; width: 225px; height: 70px; border: 1px solid #fc3; background: #ffe;'];
		ostg_ad_title_extra =  ['color: #800; font-weight: bold; font-size: 13px;',
					'color: #800; font-weight: bold; font-size: 13px;',
					'color: #800; font-weight: bold; font-size: 13px;',
					'color: #800; font-weight: bold; font-size: 13px;'];
		ostg_ad_desc = 'cursor: pointer; line-height: 16px;';
		ostg_ad_url_extra = ['color: #888; font-size: 11px;',
					'color: #888; font-size: 11px;',
					'color: #888; font-size: 11px;',
					'color: #888; font-size: 11px;'];

	} else if (ostg_style_type == 'blue') {
		ostg_google_style = 'text-align: center !important; margin: 0 auto;';
		ostg_ga_style  = 'font-size:10px; padding: 0 0 1px 0; text-align: center;';
		ostg_ga_link = 'font-size:10px; color: #ccc';						
		ostg_ad_leader  = 'overflow: hidden; width: 23%; height: 80px; background: #def; border: 2px solid #cde; margin: 0 2px 0 0; padding: 4px; text-align: left; float: left;';
		ostg_ad_title = 'font-weight: bold; color: #03c;'; 
		ostg_ad_url  = 'color: #69f;font-size:10px;'; 

		ostg_ad_leader_extra = ['width: 99%;font-size: 16px;','width: 48%;font-size: 14px;','width: 30%;font-size: 12px;','width: 23%;font-size: 11px;'];
		ostg_ad_title_extra = ['font-weight: bold; color: #03c;','font-weight: bold; color: #03c;','font-weight: bold; color: #03c;','font-weight: bold; color: #03c;'];
		ostg_ad_desc = 'cursor: pointer; line-height: 16px;';
		ostg_ad_url_extra = ['color: #69f;font-size:10px;','color: #69f;font-size:10px;','color: #69f;font-size:10px;','color: #69f;font-size:10px;'];

	} else {
		// Default values
		if (!window.ostg_google_style) { ostg_google_style = 'text-align: center !important; margin: 0 auto;'; }
		if (!window.ostg_ga_style) { ostg_ga_style  = 'font-size:10px; padding: 0 0 1px 0; text-align: center;'; }
		if (!window.ostg_ga_link) { ostg_ga_link = 'font-size:10px;'; }
		if (!window.ostg_ad_leader_extra) { ostg_ad_leader_extra = ['width: 99%;font-size: 16px;','width: 48%;font-size: 14px;','width: 32%;font-size: 12px;','width: 23%;font-size: 11px;']; }
		if (!window.ostg_ad_title_extra) { ostg_ad_title_extra = ['font-size:18px;', 'font-size:14px;', 'font-size:12px;', 'font-size:11px;']; }
		if (!window.ostg_ad_desc) { ostg_ad_desc  = 'width: 100%; cursor: pointer; color: #555;'; }
		if (!window.ostg_ad_url_extra) { ostg_ad_url_extra = ['font-size: 14px;', 'font-size:12px;', 'font-size:11px;', 'font-size:10px;']; }

		if (!window.ostg_ad_url) { ostg_ad_url  = 'color: #090;font-size:10px;'; }
		if (!window.ostg_ad_leader) { ostg_ad_leader  = 'overflow: hidden; width: 23%; height: 80px; margin: 0 2px 0 0; padding: 0 2px; text-align: left; float: left;'; }
		if (!window.ostg_ad_title) { ostg_ad_title = 'font-weight: bold;'; }
	}	

	ostg_ad_leader += ostg_ad_leader_extra[google_ads.length - 1];
	ostg_ad_title += ostg_ad_title_extra[google_ads.length - 1];
	ostg_ad_url += ostg_ad_url_extra[google_ads.length - 1];

        // Ad shell 
        document.write('<div class="google" style="height:'+ostg_ad_leader_height+'px; width:'+ostg_ad_leader_width+'px;'+ostg_google_style+'">');

	// For text ads, display each ad in turn.
	if (google_ads[0].type == 'text') {
                document.write('<div style="'+ostg_ga_style+'">');
                if (google_info.feedback_url) {
                        document.write('<a target="_blank" href="'+google_info.feedback_url+'" style="'+ostg_ga_link+'">Ads by Google</a>');
                } else {
                        document.write('Ads By Google');
                }
                document.write('</div>');

		for(i = 0; i < google_ads.length; ++i) {
			document.write('<div style="'+ostg_ad_leader+'">');
			document.write('<a href="'+google_ads[i].url+'" target="_blank" style="'+ostg_ad_title+'">'+google_ads[i].line1+'</a><br />');
			document.write('<div style="'+ostg_ad_desc+'" onclick="window.open(\''+google_ads[i].url+'\')">'+google_ads[i].line2+" "+google_ads[i].line3+'</div> ');
			document.write('<a href="'+google_ads[i].url+'" target="_blank" style="'+ostg_ad_url+'">'+google_ads[i].visible_url+'</a>');
			document.write('</div>');
		}

	// Image ads
	} else if (google_ads[0].type == 'image') {
		var orig_url = google_ads[0].image_url;
		var final_url = orig_url;
		if (window.location.protocol.match('https')) {
			if(orig_url.match('http:')) {
				final_url = orig_url.replace(/^http:/i, 'https:');
			}
		}
		final_url = final_url.replace(/googlesyndication.com/i, 'googleadservices.com');
		document.write('<a target="_blank" href="'+google_ads[0].url+'"><img src="'+final_url+'" height="'+google_ads[0].image_height+'" width="'+google_ads[0].image_width+'" border="0" alt="Ad" /></a>');

	// Flash ads
	} else if (google_ads[0].type == "flash") {

		var orig_url = google_ads[0].image_url;
		var final_url = orig_url;
		if (window.location.protocol.match('https')) {
			if(orig_url.match('http:')) {
				final_url = orig_url.replace(/^http:/i, 'https:');
			}
		}
		final_url = final_url.replace(/googlesyndication.com/i, 'googleadservices.com');

		document.write('<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000"' 
			+' codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0"' 
			+' WIDTH="' + google_ads[0].image_width 
			+'" HEIGHT="' + google_ads[0].image_height + '">' 
			+'<PARAM NAME="movie" VALUE="' + google_ads[0].image_url + '">'
			+'<PARAM NAME="quality" VALUE="high">'
			+'<PARAM NAME="AllowScriptAccess" VALUE="never">'
			+'<EMBED src="' + final_url 
			+'" WIDTH="' + google_ads[0].image_width 
			+'" HEIGHT="' + google_ads[0].image_height 
			+'" TYPE="application/x-shockwave-flash"' 
			+' AllowScriptAccess="never" ' 
			+' PLUGINSPAGE="http://www.macromedia.com/go/getflashplayer"></EMBED></OBJECT>');
	} 

	// Finish up anything that needs finishing up
	document.write ("</div>");

	window.ostg_skip += google_ads.length;
}


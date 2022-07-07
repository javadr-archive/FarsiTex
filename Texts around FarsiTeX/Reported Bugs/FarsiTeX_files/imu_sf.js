google_encoding = 'utf8';
google_ad_section = 'default';
google_image_size = '300x250';

if (window.hint) { google_hints = window.hint; }
if (!window.google_safe) { google_safe = 'high'; }
if (!window.google_max_num_ads) { google_max_num_ads = '3'; }
if (!window.google_ad_output) { google_ad_output = 'js'; }
if (!window.google_feedback) { google_feedback = 'on'; }
if (!window.ostg_ad_imu_width) { ostg_ad_imu_width  = '300'; }
if (!window.ostg_ad_imu_height) { ostg_ad_imu_height  = '250'; }

if (!window.google_ad_format) { google_ad_format = google_image_size + '_pas_abgnc'; } 

// google_oasu_url = 'http://ad.doubleclick.net/clk;39821406;13502407;y?https://adwords.google.com/select/OnsiteSignupLandingPage?client=ca-ostg_js&referringUrl=sourceforge.net'; 

currWin = window;
while (currWin.parent != currWin) {
	   currWin = currWin.parent;
}

full_url = ""+currWin.location;
if(!window.google_page_url) {
	google_page_url = ""+full_url;
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

	// Default values
	if (!window.ostg_ad_imu) { ostg_ad_imu  = 'overflow: hidden; margin: 0 0 5px 0; padding: 0 2px; text-align: left;'; }
	if (!window.ostg_ga_style) { ostg_ga_style  = 'font-size:10px; padding: 0 0 1px 0; text-align: center;'; }
	if (!window.ostg_ga_link) { ostg_ga_link = 'font-size:10px;'; }
	if (!window.ostg_ad_title) { ostg_ad_title  = 'font-weight: bold;'; }
	if (!window.ostg_ad_desc) { ostg_ad_desc  = 'width: 90%; cursor: pointer; color: #555;'; }
	if (!window.ostg_ad_url) { ostg_ad_url  = 'color: #090; font-size: 10px;'; }
	//if (!window.ostg_ad_url) { ostg_ad_url  = 'color: #090;font-size:10px;word-wrap: break-word;'; }


	if (!window.ostg_ad_imu_extra) { ostg_ad_imu_extra = ['font-size: 16px;','font-size: 14px;','font-size: 12px;','font-size: 11px;']; }
	if (!window.ostg_ad_title_extra) { ostg_ad_title_extra = ['font-size:18px;', 'font-size:14px;', 'font-size:12px;', 'font-size:11px;']; }
	if (!window.ostg_ad_url_extra) { ostg_ad_url_extra = ['font-size: 14px;', 'font-size:12px;', 'font-size:11px;', 'font-size:10px;']; }
		
	if (!window.ostg_google_style) { ostg_google_style = ' text-align: center !important; margin: 0 auto;'; }

	ostg_ad_imu += ostg_ad_imu_extra[google_ads.length - 1];
	ostg_ad_title += ostg_ad_title_extra[google_ads.length - 1];
	ostg_ad_url += ostg_ad_url_extra[google_ads.length - 1];
				
	  // Ad shell 
	document.write('<div class="google_ad" style="height:'+ostg_ad_imu_height+'px; width:'+ostg_ad_imu_width+'px;'+ostg_google_style+'">');

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
			document.write('<div style="'+ostg_ad_imu+'">');
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


/* <div class="tbarhigh">
				<b class="ttop"><b class="t1">&nbsp;</b><b class="t2">&nbsp;</b></b>
				<div class="tbox">
					<h3> Sponsor Links </h3>

				</div>
				<b class="tbtm"><b class="t2 tbg">&nbsp;</b><b class="t1 tbg">&nbsp;</b></b>
			</div>
*/

  function google_ad_request_done(ads) {
    /*
     * This function is required, but may be left blank
     * if no ads are required.
     */
  }

  function google_radlink_request_done(radlinks) {
    /*
     * This function is required and is used to display
     * the ads that are returned from the JavaScript
     * request. You should modify the document.write
     * commands so that the HTML they write out fits
     * with your desired Link Unit layout.
     */
	 
    if (radlinks.length < 1) 
      return; 
    document.write('<div style="text-align: left; background: #fff;"> <div class="tbarhigh"><div class="tbar"><b class="ttop"><b class="t1">&nbsp;</b><b class="t2">&nbsp;</b></b>');
    document.write('   <div class="tbox"><h3>Ad Categories</h3></div>');
    document.write(' <b class="tbtm"><b class="t2 tbg">&nbsp;</b><b class="t1 tbg">&nbsp;</b></b></div>');
    document.write(' <ul class="clean">');
    for(i=0; i < radlinks.length; ++i) {
		 var rdurl = "http://genweb.ostg.com/google/radlinks/sf_bottom_right_results.html?google_kw=" + radlinks[i].url_escaped_term + "&google_page_url=" + window.location;
		 document.write("<li><a target=\"_top\" href=\"" + rdurl + "\">" + radlinks[i].term + "</a></li>\n");
    }
	 document.write("</ul>");
    document.write('</div>');
    document.write('</div>');
 }
full_url = ""+window.location;
if (full_url.match(/prdownloads.sourceforge.net\/(\w+)/)) {
			google_page_url = 'http://sourceforge.net/projects/' + RegExp.$1;
}
if (window.sf_proj_home) { google_page_url = sf_proj_home; }
google_ad_client = 'ca-ostg-radlinks_js';
google_ad_channel = 'sourceforge';
google_ad_output = 'js';
google_max_num_ads = '0';
google_encoding = 'utf-8';
 //    google_kw = 'open+source+software';
//     google_kw_type = 'broad';
google_safe = 'high';
google_num_radlinks = '5';
google_max_radlink_len = '35';
google_rl_filtering = 'high';
google_rl_mode = 'relevance';

/*
 * The JavaScript returned from the following page
 * uses the parameter values assigned above to populate
 * an array of Google Link Unit objects. Once that array
 * has been populated, the JavaScript will call the two
 * functions at the beginning of this JavaScript sample
 * to display the Link Units.
 */
document.write('<script language="JavaScript" src="http://pagead2.googlesyndication.com/pagead/show_ads.js"> </script>');



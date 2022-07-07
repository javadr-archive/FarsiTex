function load(){
wfrm.wgemail.onblur=b2;
wfrm.wgname.onblur=b1;
wfrm.wgemail.onfocus=f2;
wfrm.wgname.onfocus=f1;
wfrm.wgname.value='نام شما'
wfrm.wgemail.value='ايميل شما'
}
window.onload=load;

function b2(){
if (wfrm.wgemail.value==''){
wfrm.wgemail.value='ايميل شما'
}
}

function b1(){
if (wfrm.wgname.value==''){
wfrm.wgname.value='نام شما'
}
}
function f2(){
if (wfrm.wgemail.value=='ايميل شما'){
wfrm.wgemail.value=''
}
}

function f1(){
if (wfrm.wgname.value=='نام شما'){
wfrm.wgname.value=''
}
}

function wgcheckMail(Expression)
{
	var x = Expression;
	var filter  = /^([a-zA-Z0-9_\.\-])+\@(([a-zA-Z0-9\-])+\.)+([a-zA-Z0-9]{2,4})+$/;
	if (filter.test(x)) return true;
	else return false;
}


function sp(el) {
    if (el.wgname.value=='') {
		alert ('نام خالى است');
		el.wgname.focus();                          
		return false;                          
	}
	if (el.wgname.value=='نام شما') {                          
		alert ('نام خالى است');                          
		el.wgname.focus();                          
		return false;
	}
	if (el.wgemail.value=='ايميل شما') {                          
		alert ('پست الکترونيکى خالى است');                          
		el.wgemail.focus();                          
		return false;                          
	}
	if (el.wgemail.value=='') {                          
		alert ('پست الکترونيکى خالى است');                          
		el.wgemail.focus();                          
		return false;                          
	}
	if (!wgcheckMail(el.wgemail.value)) {                          
		alert ('پست الکترونيکى مجاز نمى باشد');                          
		el.wgemail.focus();                          
		el.wgemail.select();
		return false;
	}
	return true;
	}
	
	
	
document.write('<style>.txts{font-family:tahoma;width:130px;font-size:9pt};.txtb{font-family:tahoma;font-size:9pt};.txta{font-family:tahoma;font-size:7pt}</style>');
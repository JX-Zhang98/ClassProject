function check_user()
{
	var user = document.getElementById("user").value;
	var mail=/^[\s\S]+?@[\s\S]+?.com$/;
	var num=/^\d+$/;
	if(user.match(mail) || (user.match(num) && user.length==11))
	{
		document.getElementById("namejudge").style.color = "blue";
		document.getElementById("namejudge").style.fontFamily="微软雅黑";
		document.getElementById("namejudge").style.fontSize="1em";
        document.getElementById("namejudge").innerText = "Accepted";
	}
	else
	{
		document.getElementById("namejudge").style.color = "red";
		document.getElementById("namejudge").style.fontFamily="微软雅黑";
		document.getElementById("namejudge").style.fontSize="1em";
        document.getElementById("namejudge").innerText = "Wrong";
	}
}
function check_psd()
{
	var psd = document.getElementById("psd").value;
	if(psd.length<6)
	{
		document.getElementById("psdjudge").style.color = "red";
		document.getElementById("psdjudge").style.fontFamily="微软雅黑";
		document.getElementById("psdjudge").style.fontSize="1em";
        document.getElementById("psdjudge").innerText = "Too short";
	}
	else{
		document.getElementById("psdjudge").style.color = "yellow";
		document.getElementById("psdjudge").style.fontFamily="微软雅黑";
		document.getElementById("psdjudge").style.fontSize="1em";
        document.getElementById("psdjudge").innerText = "";
	}	
}

function confirm_psd(){
	var psd=document.getElementById("psd").value;
	var psdd=document.getElementById("confirmpsd").value;
	if(psd.match(psdd)&&psd.length==psdd.length || psdd.length==0){
		document.getElementById("tpsdjudge").style.color = "yellow";
		document.getElementById("tpsdjudge").style.fontFamily="微软雅黑";
		document.getElementById("tpsdjudge").style.fontSize="1em";
        document.getElementById("tpsdjudge").innerText = "";
	}
	else{
		document.getElementById("tpsdjudge").style.color = "red";
		document.getElementById("tpsdjudge").style.fontFamily="微软雅黑";
		document.getElementById("tpsdjudge").style.fontSize="1em";
        document.getElementById("tpsdjudge").innerText = "Not same";
	}
}
function check_mail(){
	var mail=document.getElementById("mail").value;
	var test=/^[\s\S]+?@[\s\S]+?.com$/;
	if(mail.match(test) || mail.length==0){
		document.getElementById("mailjudge").style.color = "yellow";
		document.getElementById("mailjudge").style.fontFamily="微软雅黑";
		document.getElementById("mailjudge").style.fontSize="1em";
        document.getElementById("mailjudge").innerText = "";
	}
	else{
		document.getElementById("mailjudge").style.color = "red";
		document.getElementById("mailjudge").style.fontFamily="微软雅黑";
		document.getElementById("mailjudge").style.fontSize="1em";
        document.getElementById("mailjudge").innerText = "Wrong";
	}
}
















<!--
var T_INFOVERZ=12; //Verzögerung, während der kein neuer Mouseover-Infotext angezeigt wird
var T_HGVERZ=18;   //Verzögerung, bis wieder der allgemeine Infotext angezeigt wird

var col;
var hcol;
var icol;

var speed=50;
var ustep=0;
var oinstep=16;
var faktor=16;

var imo=0;
var ihg=0;
var isMOver=false;

var nr_akt=0;
var nr_bak=0;
var cont_akt;
var cont_bak;


function i_showElem(inr) {
  if (inr == 0){
	if (isMOver == true) {
		isMOver = false;

		//Hintergrund-Timer starten
		if (ihg <= 0) {
			ihg = T_HGVERZ;
			tmr_HgVerz();
		}
		else {
			ihg = T_HGVERZ;
		}
	}
  }
  else{
	if (ihg > 0) {
		ihg = 0;
	}

	isMOver = true;

	if (inr != nr_akt){

		if (nr_bak==0){
			cont_bak = "i_content";
		}
		else{
			cont_bak = "i_content" + nr_bak;
		}
		document.getElementById(cont_bak).style.visibility='hidden';

		//In dieser Variablen ist immer die aktuelle Mouseoverinfo
		nr_bak=nr_akt;
		nr_akt=inr;

		if (imo <= 0) {
			if (nr_bak==0){
				cont_bak = "i_content";
			}
			else{
				cont_bak = "i_content" + nr_bak;
			}
			document.getElementById(cont_bak).style.visibility='hidden';

			if (nr_akt==0){
				cont_akt = "i_content";
			}
			else{
				cont_akt = "i_content" + nr_akt;
			}
			document.getElementById(cont_akt).style.visibility='visible';

			icol=oinstep;
			fadeMo();

			imo = T_INFOVERZ;
			tmr_MoVerz();
		}
		else {
			imo = T_INFOVERZ;
		}

	}
  }
}
    
function tmr_HgVerz() {
  ihg--;

//  Prüfroutine
//  document.getElementById("c_pfad").innerText=nr_bak + "   " + nr_akt + "   " + cont_bak + "   " + cont_akt;

  if (ihg > 0) {
    setTimeout("tmr_HgVerz()",speed);
  }
  else {
    ihg = 0;

    if (isMOver == false) {
      document.getElementById(cont_akt).style.visibility='hidden';

      nr_akt=0;
      cont_akt = "i_content";
      document.getElementById(cont_akt).style.visibility='visible';
      hcol=oinstep;
      fadeHg();
    }
  }
}

function tmr_MoVerz() {
  imo--;

//  Prüfroutine
//  document.getElementById("c_pfad").innerText=nr_bak + "   " + nr_akt + "   " + cont_bak + "   " + cont_akt;

  if (imo > 0) {
    setTimeout("tmr_MoVerz()",speed);
  }
  else {
    imo = 0;

    if (isMOver == true){
      if (cont_akt != "i_content" + nr_akt){
        document.getElementById(cont_akt).style.visibility='hidden';

        if (nr_akt==0){
          cont_akt = "i_content";
        }
        else{
          cont_akt = "i_content" + nr_akt;
        }
        document.getElementById(cont_akt).style.visibility='visible';
        icol=oinstep;
        fadeMo();
      }
      else if (document.getElementById(cont_akt).style.visibility=='hidden') {
        document.getElementById(cont_akt).style.visibility='visible';
      }
    }
  }
}

function fadeHg() {
  hcol--;
  col=hcol*faktor;
  document.getElementById("i_content").style.color='rgb(' + col + ',' + col + ',' + col + ')';
	
  if (hcol>ustep) {
    setTimeout("fadeHg()",speed);
  }
}

function fadeMo() {
  icol--;
  col=icol*faktor;
  document.getElementById(cont_akt).style.color='rgb(' + col + ',' + col + ',' + col + ')';
	
  if (icol>ustep) {
    setTimeout("fadeMo()",speed);
  }
}

//-->
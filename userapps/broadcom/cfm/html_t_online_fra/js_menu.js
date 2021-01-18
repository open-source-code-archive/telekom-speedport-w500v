<!--
  function rahmen(high,nr){
      if (high==1){
        document.getElementById("t_but" + nr).style.color='#E20074';
        document.getElementById("t_but" + nr).style.borderColor='#E20074';
      }
      else{
        document.getElementById("t_but" + nr).style.color='#000000';
        document.getElementById("t_but" + nr).style.borderColor='#666666';
      }
  }

  function isNIP(seg1,seg2,seg3,seg4){
    var prf=0;

    if (seg1.value == "" && seg2.value == "" && seg3.value == "" && seg4.value == ""){
      prf = -1;
      seg1.focus();
    }
    else{
      if (seg4.value == "" || isNaN(seg4.value) || seg4.value < 0 || seg4.value > 255){
        prf = 4;
        seg4.value="";
        seg4.focus();
      }
      if (seg3.value == "" || isNaN(seg3.value) || seg3.value < 0 || seg3.value > 255){
        prf = 3;
        seg3.value="";
        seg3.focus();
      }
      if (seg2.value == "" || isNaN(seg2.value) || seg2.value < 0 || seg2.value > 255){
        prf = 2;
        seg2.value="";
        seg2.focus();
      }
      if (seg1.value == "" || isNaN(seg1.value) || seg1.value < 0 || seg1.value > 255){
        prf = 1;
        seg1.value="";
        seg1.focus();
      }
    }

    return prf;

  }

  function isNDatum(mtag,monat,jahr){
    var prf=0;

    if (mtag.value == "" && monat.value == "" && jahr.value == ""){
      prf = -1;
      mtag.focus();
    }
    else{
      if (jahr.value == "" || isNaN(jahr.value)){
        prf = 3;
        jahr.value="";
        jahr.focus();
      }
      if (monat.value == "" || isNaN(monat.value) || monat.value < 1 || monat.value > 12){
        prf = 2;
        monat.value="";
        monat.focus();
      }
      if (mtag.value == "" || isNaN(mtag.value) || mtag.value < 1 || mtag.value > 31
       || (mtag.value == 31 && (monat.value == 4 || monat.value == 6 || monat.value == 9 || monat.value == 11))
       || (mtag.value == 30 && monat.value == 2)){
        prf = 1;
        mtag.value="";
        mtag.focus();
      }
    }

    return prf;

  }

  function isNTime(stunde,minute){
    var prf=0;

    if (stunde.value == "" && minute.value == ""){
      prf = -1;
      //stunde.focus();
    }
    else{
      if (minute.value == "" || isNaN(minute.value) || minute.value < 0 || minute.value > 59){
        prf = 2;
        minute.value="";
        //minute.focus();
      }
      if (stunde.value == "" || isNaN(stunde.value) || stunde.value < 0 || stunde.value > 23){
        prf = 1;
        stunde.value="";
        //stunde.focus();
      }
    }

    return prf;

  }

  function isNHex(str_prf){
  var shex = "0123456789abcdef";
  var sprf;
  var prfok = false;

    sprf = str_prf.toLowerCase();

    for(p=0;p<sprf.length;p++){
      if(shex.indexOf(sprf.substr(p,1)) == -1){
        prfok = true;
        break;
      }
    }

    return prfok;
  }
  
  function isNEmail(str_prf){
  var prfok = false;

    if (str_prf.length < 5){
      prfok = true;
    }
    else{
      var tst_at = str_prf.indexOf("@");
      var tst_pt = str_prf.lastIndexOf(".");
      if (tst_at < 1 || tst_at > str_prf.length-4){
        prfok = true;
      }
      else if (tst_pt < 3 || tst_pt > str_prf.length-2){
        prfok = true;
      }
      else if (tst_at > tst_pt-2){
        prfok = true;
      }
    }

    return prfok;
  }

  function restart(){
      //top.frames[1].location.href = "m_start_passwort.htm";
      //top.frames[2].location.href = "index.htm";
      top.frames[2].location.href = "index_restart_prev.htm";
  }
  
    function budstart(){
      top.frames[1].location.href = "m_start_passwort.htm";
      top.frames[2].location.href = "hcti_status_budget_pc.htm"
  }

  function assistent(){
      top.frames[0].m_akt=2;
      top.frames[1].location.href = "m_assistent.htm";
      top.frames[2].location.href = "hcti_assistent_1.htm";
  }

function loadassistent(){
      top.frames[0].asspwd = "";
      top.frames[0].assnewpwd = "";
      
      top.frames[0].assprovtxt1[0] = top.frames[2].provtxt1[0];
      top.frames[0].assprovtxt1[1] = top.frames[2].provtxt1[1];
      top.frames[0].assprovtxt1[2] = top.frames[2].provtxt1[2];
      top.frames[0].assprovtxt1[3] = top.frames[2].provtxt1[3];
      
      top.frames[0].assprovtxt2[0] = top.frames[2].provtxt2[0];
      top.frames[0].assprovtxt2[1] = top.frames[2].provtxt2[1];
      top.frames[0].assprovtxt2[2] = top.frames[2].provtxt2[2];
      top.frames[0].assprovtxt2[3] = top.frames[2].provtxt2[3];
      
      top.frames[0].assprovtxt3[0] = top.frames[2].provtxt3[0];
      top.frames[0].assprovtxt3[1] = top.frames[2].provtxt3[1];
      top.frames[0].assprovtxt3[2] = top.frames[2].provtxt3[2];
      top.frames[0].assprovtxt3[3] = top.frames[2].provtxt3[3];
      
      top.frames[0].assprovpwd[0] = top.frames[2].provpwd[0];
      top.frames[0].assprovpwd[1] = top.frames[2].provpwd[1];
      top.frames[0].assprovpwd[2] = top.frames[2].provpwd[2];
      top.frames[0].assprovpwd[3] = top.frames[2].provpwd[3];
      
      top.frames[0].assprovider = top.frames[2].provider;
      top.frames[0].assssid = top.frames[2].ssid;
      top.frames[0].assssidhide = top.frames[2].ssidhide;
      top.frames[0].asswep = top.frames[2].wep;
      top.frames[0].assencrypt = top.frames[2].encrypt;
      top.frames[0].asswepkeylength = top.frames[2].wepkeylength;
      top.frames[0].asswepkeytyp = top.frames[2].wepkeytyp;
      top.frames[0].asswepkey1 = top.frames[2].wepkey1;
      top.frames[0].asswepkey2 = top.frames[2].wepkey2;
      top.frames[0].asswepkey3 = top.frames[2].wepkey3;
      top.frames[0].asswepkey4 = top.frames[2].wepkey4;
      top.frames[0].asswpapsk = top.frames[2].wpapsk;
      top.frames[0].mix_asswpapak = top.frames[2].mix_wpapsk;
      top.frames[0].asswepkeyindex = top.frames[2].wepkeyindex;
	  

}



function loadcfg(){
      top.frames[0].cfgprovtxt1[0] = top.frames[2].provtxt1[0];
      top.frames[0].cfgprovpwd[0] = top.frames[2].provpwd[0];
      top.frames[0].cfgprovpwd[1] = top.frames[2].provpwd[1];
      top.frames[0].cfgprovpwd[2] = top.frames[2].provpwd[2];
      top.frames[0].cfgprovpwd[3] = top.frames[2].provpwd[3];
}

 
function start(){
	top.frames[0].m_akt=1;
	top.frames[1].location.href = "m_startseite.htm";
	top.frames[2].location.href = "hcti_startseite.htm";
}
 
  function menupkt(nr, url){
      top.frames[0].m_akt=nr;
      top.frames[2].location.href = url;

      for(i=0;i<top.frames[1].mpkt.length;i++){
        top.frames[1].document.getElementById("m_but" + top.frames[1].mpkt[i]).style.color='#000000';
        top.frames[1].document.getElementById("m_but" + top.frames[1].mpkt[i]).style.backgroundImage='none';
      }

      top.frames[1].document.getElementById("m_but" + nr).style.color='#FFFFFF';
      top.frames[1].document.getElementById("m_but" + nr).style.backgroundImage='url(pic_m_marker.gif)';
  }
	
  function startseite(){
      menupkt(1,"hcti_startseite.htm");
  }
  function sicherheit(){
      menupkt(31,"hcti_sicherheit.htm");
  }
  function netzwerk(){
      menupkt(32,"hcti_netzwerk.htm");
  }
  function budget(){
      menupkt(33,"budget.cmd?action=view");
  }
  function status(){
      menupkt(6,"hcti_status.htm");
  }
  function hilfsmittel(){
      menupkt(51,"hcti_hilfsmittel.htm");
  }
  function laden(){
      menupkt(52,"hcti_laden.htm");
  }
  function beenden(){
    	menupkt(6,"hcti_startseite.htm");
	top.frames[2].location.href="logout.cmd";
	top.frames[1].document.getElementById("m_but6").style.color='#FFFFFF';
      	top.frames[1].document.getElementById("m_but6").style.backgroundImage='url(pic_m_marker.gif)';
  }

function isHexaDigit(digit) {
   var hexVals = new Array("0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                           "A", "B", "C", "D", "E", "F", "a", "b", "c", "d",
"e", "f");
   var len = hexVals.length;
   var i = 0;
   var ret = false;
                                                                                
   for ( i = 0; i < len; i++ )
      if ( digit == hexVals[i] ) break;
                                                                                
   if ( i < len )
      ret = true;
                                                                                
   return ret;
}

function isValidKey(val, size) {
   var ret = false;
   var len = val.length;
   var dbSize = size * 2;
                                                                                
   if ( len == size )
      ret = true;
   else if ( len == dbSize ) {
      for ( i = 0; i < dbSize; i++ )
         if ( isHexaDigit(val.charAt(i)) == false )
            break;
      if ( i == dbSize )
         ret = true;
   } else
      ret = false;
                                                                                
   return ret;
}

function isNameUnsafe(compareChar) {
   var unsafeString = "\"<>%\\^[]`\+\$\,='#&@.: \t";
                                                                                
   if ( unsafeString.indexOf(compareChar) == -1 && compareChar.charCodeAt(0) > 32 && compareChar.charCodeAt(0) < 123 )
      return false; // found no unsafe chars, return false
   else
      return true;
}

function isValidName(name) {
   var i = 0;
                                                                                
   for ( i = 0; i < name.length; i++ ) {
      if ( isNameUnsafe(name.charAt(i)) == true )
         return false;
   }
                                                                                
   return true;
}

function isSameSubNet(lan1Ip, lan1Mask, lan2Ip, lan2Mask) {
                                                                                
   var count = 0;
                                                                                
   lan1a = lan1Ip.split('.');
   lan1m = lan1Mask.split('.');
   lan2a = lan2Ip.split('.');
   lan2m = lan2Mask.split('.');
                                                                                
   for (i = 0; i < 4; i++) {
      l1a_n = parseInt(lan1a[i]);
      l1m_n = parseInt(lan1m[i]);
      l2a_n = parseInt(lan2a[i]);
      l2m_n = parseInt(lan2m[i]);
      if ((l1a_n & l1m_n) == (l2a_n & l2m_n))
         count++;
   }
   if (count == 4)
      return true;
   else
      return false;
}

function isValidIpAddress(address) {
   var i = 0;
                                                                                
   if ( address == '0.0.0.0' ||
        address == '255.255.255.255' )
      return false;
                                                                                
   addrParts = address.split('.');
   if ( addrParts.length != 4 ) return false;
                                                                                
   for (i = 0; i < 4; i++) {
      num = parseInt(addrParts[i])
      if ( isNaN(num) )
         return false;
      if ( num < 0 || num > 255 )
         return false;
   }
                                                                                
   return true;
}

function getLeftMostZeroBitPos(num) {
   var i = 0;
   var numArr = [128, 64, 32, 16, 8, 4, 2, 1];
                                                                                
   for ( i = 0; i < numArr.length; i++ )
      if ( (num & numArr[i]) == 0 )
         return i;
                                                                                
   return numArr.length;
}

function getRightMostOneBitPos(num) {
   var i = 0;
   var numArr = [1, 2, 4, 8, 16, 32, 64, 128];
                                                                                
   for ( i = 0; i < numArr.length; i++ )
      if ( ((num & numArr[i]) >> i) == 1 )
         return (numArr.length - i - 1);
                                                                                
   return -1;
}

function isValidSubnetMask(mask) {
   var i = 0, num = 0;
   var zeroBitPos = 0, oneBitPos = 0;
   var zeroBitExisted = false;
                                                                                
   if ( mask == '0.0.0.0' )
      return false;
                                                                                
   maskParts = mask.split('.');
   if ( maskParts.length != 4 ) return false;
                                                                                
   for (i = 0; i < 4; i++) {
      if ( isNaN(maskParts[i]) == true )
         return false;
      num = parseInt(maskParts[i]);
      if ( num < 0 || num > 255 )
         return false;
      if ( zeroBitExisted == true && num != 0 )
         return false;
      zeroBitPos = getLeftMostZeroBitPos(num);
      oneBitPos = getRightMostOneBitPos(num);
      if ( zeroBitPos < oneBitPos )
         return false;
      if ( zeroBitPos < 8 )
         zeroBitExisted = true;
   }
                                                                                
   return true;
}

function isValidPort(port) {
   var fromport = 0;
   var toport = 100;
                                                                                
   portrange = port.split(':');
   if ( portrange.length < 1 || portrange.length > 2 ) {
       return false;
   }
   if ( isNaN(portrange[0]) )
       return false;
   fromport = parseInt(portrange[0]);
                                                                                
   if ( portrange.length > 1 ) {
       if ( isNaN(portrange[1]) )
          return false;
       toport = parseInt(portrange[1]);
       if ( toport <= fromport )
           return false;
   }
                                                                                
   if ( fromport < 1 || fromport > 65535 || toport < 1 || toport > 65535 )
       return false;
                                                                                
   return true;
}

function isValidNatPort(port) {
   var fromport = 0;
   var toport = 100;
                                                                                
   portrange = port.split('-');
   if ( portrange.length < 1 || portrange.length > 2 ) {
       return false;
   }
   if ( isNaN(portrange[0]) )
       return false;
   fromport = parseInt(portrange[0]);
                                                                                
   if ( portrange.length > 1 ) {
       if ( isNaN(portrange[1]) )
          return false;
       toport = parseInt(portrange[1]);
       if ( toport <= fromport )
           return false;
   }
                                                                                
   if ( fromport < 1 || fromport > 65535 || toport < 1 || toport > 65535 )
       return false;
                                                                                
   return true;
}

function isValidMacAddress(address) {
   var c = '';
   var i = 0, j = 0;
                                                                                
   if ( address == 'ff:ff:ff:ff:ff:ff' ) return false;
                                                                                
   addrParts = address.split(':');
   if ( addrParts.length != 6 ) return false;
                                                                                
   for (i = 0; i < 6; i++) {
      for ( j = 0; j < addrParts[i].length; j++ ) {
         c = addrParts[i].toLowerCase().charAt(j);
         if ( (c >= '0' && c <= '9') ||
              (c >= 'a' && c <= 'f') )
            continue;
         else
            return false;
      }
   }
                                                                                
   return true;
}

var hexVals = new Array("0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
              "A", "B", "C", "D", "E", "F");
var unsafeString = "\"<>%\\^[]`\+\$\,'#&";
// deleted these chars from the include list ";", "/", "?", ":", "@", "=", "&"
// and #
// so that we could analyze actual URLs
                                                                                
function isUnsafe(compareChar)
// this function checks to see if a char is URL unsafe.
// Returns bool result. True = unsafe, False = safe
{
   if ( unsafeString.indexOf(compareChar) == -1 && compareChar.charCodeAt(0) >
32
        && compareChar.charCodeAt(0) < 123 )
      return false; // found no unsafe chars, return false
   else
      return true;
}

function decToHex(num, radix)
// part of the hex-ifying functionality
{
   var hexString = "";
   while ( num >= radix ) {
      temp = num % radix;
      num = Math.floor(num / radix);
      hexString += hexVals[temp];
   }
   hexString += hexVals[num];
   return reversal(hexString);
}

function reversal(s)
// part of the hex-ifying functionality
{
   var len = s.length;
   var trans = "";
   for (i = 0; i < len; i++)
      trans = trans + s.substring(len-i-1, len-i);
   s = trans;
   return s;
}
                                                                                
function convert(val)
// this converts a given char to url hex form
{
   return  "%" + decToHex(val.charCodeAt(0), 16);
}

function encodeUrl(val)
{
   var len     = val.length;
   var i       = 0;
   var newStr  = "";
   var original = val;
                                                                                
   for ( i = 0; i < len; i++ ) {
      if ( val.substring(i,i+1).charCodeAt(0) < 255 ) {
         // hack to eliminate the rest of unicode from this
         if (isUnsafe(val.substring(i,i+1)) == false)
            newStr = newStr + val.substring(i,i+1);
         else
            newStr = newStr + convert(val.substring(i,i+1));
      } else {
         // woopsie! restore.
         alert ("Found a non-ISO-8859-1 character at position: " + (i+1) +
",\nPlease eliminate before continuing.");
         newStr = original;
         // short-circuit the loop and exit
         i = len;
      }
   }
   return newStr;
}

var markStrChars = "\"'";
                                                                                
// Checks to see if a char is used to mark begining and ending of string.
// Returns bool result. True = special, False = not special
function isMarkStrChar(compareChar)
{
   if ( markStrChars.indexOf(compareChar) == -1 )
      return false; // found no marked string chars, return false
   else
      return true;
}

// use backslash in front one of the escape codes to process
// marked string characters.
// Returns new process string
function processMarkStrChars(str) {
   var i = 0;
   var retStr = '';
                                                                                
   for ( i = 0; i < str.length; i++ ) {
      if ( isMarkStrChar(str.charAt(i)) == true )
         retStr += '\\';
      retStr += str.charAt(i);
   }
                                                                                
   return retStr;
}

// function added by eric,check if user enter an invalid value
function isValid() {
        var ieKey = event.keyCode;
        if(ieKey < 48 || ieKey > 57)
                event.keyCode = 0 ;
}
                                                                                
function isValidMulti() {
        var ieKey = event.keyCode;
        if(ieKey < 44 || ieKey > 57 || ieKey ==46 || ieKey ==47)
                event.keyCode = 0;
}

function isSpecialChars(s) {
        var src = new String(s);
        var lst = new String('\"\'');
        var i, n;
        n = lst.length;
        for (i=0; i<n; i++) {
                var c = lst.charAt(i);
                var tmpS = new String(c);
                if (src.indexOf(tmpS) != -1) {
                        return true;
                }
        }
        return false;
}

//-->

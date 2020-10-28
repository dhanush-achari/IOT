#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char ASCII_conv[] PROGMEM = R"=====(
<html>  
<head>  
<script type="text/javascript">  
function convert(ch){  
 var index=0;
 var i=ch.charCodeAt(index);
 document.getElementById("ass").value=i;
}  
</script>  
</head>  
<body>  
<p><h1><center>ASCII CONVERTER</h1></center></p>  
<form action="/action_page">  
<h3><b>User Input</b></h3>
<input type="text" id="alp" name="alpha" placeholder="Alphabet" required="req" oninput="convert(this.value)" onchange="convert(this.value)">
<h3><b>ASCII Code</b></h3>
<input type="text" id="ass" name="ascii" placeholder="ascii">
<input type="submit" name="sub">
</form>  
</body>  
</html>  

)=====";

const int A=D1;
const int B=D2;
const int C=D3;
const int D=D4;
const int E=D6;
const int F=D7;
const int G=D8;

const char* ssid = "spectra";
const char* password = "Danush@singam123";

ESP8266WebServer server;

void handleRoot()
{
  server.send_P(200,"text/html",ASCII_conv);
}
void handleSub()
{
  String a = server.arg("ascii");
  String i = server.arg("alpha");

  Serial.print("The alphabet entered is=");
  Serial.println(i);
  Serial.print("The corresponding ascii code=");
  Serial.println(a);
  String s = "<html><body><center><h1> VALUES SUBMITTED TO ESP8266</h1></center></body></html>";
  server.send(200 ,"text/html", s);

  int n = a.toInt();

  while(n!=0)
  {
    int rem=n%10;
    n=n/10;
    sevenSeg(rem);
    Serial.println(rem);
    delay(2500);
  }

  
}
void setup(void){

  pinMode(A,OUTPUT);  digitalWrite(A,LOW);
  pinMode(B,OUTPUT);  digitalWrite(B,LOW);
  pinMode(C,OUTPUT);  digitalWrite(C,LOW);
  pinMode(D,OUTPUT);  digitalWrite(D,LOW);
  pinMode(E,OUTPUT);  digitalWrite(E,LOW);
  pinMode(F,OUTPUT);  digitalWrite(F,LOW);
  pinMode(G,OUTPUT);  digitalWrite(G,LOW);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router

 Serial.begin(115200);
  
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println("WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

   server.on("/",handleRoot);
   server.on("/action_page",handleSub);

   server.begin();
   Serial.println("HTTP server started");
 }

void loop(void){
  server.handleClient();          //Handle client requests
}


void sevenSeg(int num){ 
   if(num==0){
     onA(); onB(); onC(); onD(); onE(); onF();
      offG();
      }
    else if(num==1){
      onB(); onC();
      offA(); offD(); offE(); offF(); offG();
      }
    else if(num==2){
      onA(); onB(); onG(); onE(); onD();
      offF(); offC();
      }
    else if(num==3){
      onA(); onB(); onG(); onC(); onD();
      offE(); offF();
      }
    else if(num==4){
      onF(); onG(); onB(); onC();
      offA(); offE(); offD();
      }
    else if(num==5){
      onA(); onF(); onG(); onC(); onD();
      offB(); offE();
      }
    else if(num==6){
      onA(); onC(); onD(); onE(); onF(); onG();
      offB();
      }
    else if(num==7){
      onA(); onB(); onC();
      offD(); offE(); offF(); offG();
      }
    else if(num==8){
      offA(); offB(); offC(); offD(); offE(); offF(); offG();
      }
    else if(num==9){
      onA(); onB(); onC(); onF(); onG();
      offE(); offD();
      } 
}
/*THESE FUNCTIONS ARE SELF EXPLATNATORY FOR CONTROLLING(ON/OFF) THE 7SEGMENT LED DISPLAY */
void onA(){ digitalWrite(A,HIGH);} void offA(){ digitalWrite(A,LOW);}
void onB(){ digitalWrite(B,HIGH);} void offB(){ digitalWrite(B,LOW);}
void onC(){ digitalWrite(C,HIGH);} void offC(){ digitalWrite(C,LOW);}
void onD(){ digitalWrite(D,HIGH);} void offD(){ digitalWrite(D,LOW);}
void onE(){ digitalWrite(E,HIGH);} void offE(){ digitalWrite(E,LOW);}
void onF(){ digitalWrite(F,HIGH);} void offF(){ digitalWrite(F,LOW);}
void onG(){ digitalWrite(G,HIGH);} void offG(){ digitalWrite(G,LOW);}

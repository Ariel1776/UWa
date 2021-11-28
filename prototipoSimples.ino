#include <ESP8266WiFi.h>

IPAddress DHCP(192, 168, 18, 11);
IPAddress Getway(192, 168, 18, 1);
IPAddress Mask(255, 255, 255, 0);

const char* sta_ssid = "Nome da rede";
const char* sta_pass = "Senha da rede";

WiFiServer server(80);   //cria servidor "server", parametro porta 80

void setup() {
    Serial.begin(115200);
    pinMode(2, INPUT);
    WiFi.mode(WIFI_STA);  // iniciando modo de operação como estação/ponto de acesso
    Serial.print("Connecting to ");
    Serial.print(sta_ssid);
 
    WiFi.begin(sta_ssid, sta_pass);
  
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
        //digitalWrite(LED_BUILTIN,HIGH); 
        delay(50);
        //digitalWrite(LED_BUILTIN,LOW);  
    }
    
    Serial.println("");
    Serial.println("WiFi connected");
        
    // Start the server
    server.begin();
    Serial.println("Server started");
    Serial.print("STA IP : ");
    Serial.println(WiFi.localIP());
}

void loop() {
    WiFiClient client = server.available(); // chega se o servidor esta disponivel
    if (!client) {                          // retorna o loop caso não tenha cliente
        return;
    }
    Serial.println("new client");
    while(!client.available()){ // aguarda ate que o client envie os dados
        delay(10);
    }
  
    
    String req = client.readStringUntil('\r');
    Serial.println(req);
    client.flush();

    String webpage = "<h1>Bem vindo a Projeto Detector de COVID-19</h1><h2></h2>";
    
    
    if (digitalRead(2)){webpage += "<div>Tem COVID</div>";}
    if (!digitalRead(2)){webpage += "<div>NAO Tem COVID</div>";}   

    if ((req.indexOf("/") != -1)){client.print(webpage);}
    client.flush();
    client.stop();  // The client will actually be disconnected
    Serial.println("Client disonnected"); 
    req = "";
    delay(200);

    return;  // when the function returns and 'client' object is destroyed
}

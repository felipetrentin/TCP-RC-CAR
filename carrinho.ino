#include <ESP8266WiFi.h>
#include <WiFiServer.h>

#define in1 15
#define in2 13
#define in3 12
#define in4 14
#define ena 0
#define enb 4

#define led1 2
#define led2 16


struct datastruct {
    short int motorspeed;// 2
    short int steering;// 2
};
#define nob sizeof(datastruct) //num of bytes
union inputFromPC {
   datastruct moveData;
   byte pcLine[nob];
};
inputFromPC inputData;
boolean armed = false;
WiFiServer sv(1000);//Cria o objeto servidor com tal porta
WiFiClient cl;//Cria o objeto cliente.


void setup() {
  //pinmodes
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  //valores padrão
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  analogWriteFreq(250);//freq. pwm
  Serial.begin(115200);//Habilita a comm serial.
  WiFi.mode(WIFI_AP);//Define o WiFi como Acess_Point.
  WiFi.softAP("Car", "");//Cria a rede de Acess_Point.
  sv.begin();//Inicia o servidor TCP na porta declarada no começo.
  Serial.println(WiFi.softAPIP());//mostar ip
  Serial.println("started");
}

void loop() {
  if (cl.connected())//Detecta se há clientes conectados no servidor.
    {
        digitalWrite(led2, LOW);
        receiveData();
    }
    else//Se nao houver cliente conectado,
    {
        digitalWrite(led2, HIGH);
        cl = sv.available();//Disponabiliza o servidor para o cliente se conectar.
        drive(0);
        steer(0);
        delay(1);
    }
}

//CODIGO COMPATIBLE PARA LA mayoria de GSM/GPS para SIM 900,SIM908,SIM808,M90
//Comando usados:
//enviar senal para CERRAR CANDADO: codigo @BOBON para encender la bobina y cerrar el candado
//enviar senal para ACTVIAR GPS: codgio @GPS para que se envie el mensaje de longitu y latitud
//No utilizar pin9 en el SIM808

#include <TinyGPS.h>
#include <SoftwareSerial.h>
TinyGPS gps;
SoftwareSerial Serial1(10,11);
int i =0;
int j =0;
float lati,longi =0;
String latitud,longitud,maps,datos;
char DAT_GPS;
float flat,flon;
char numero_cell[] = "XXXXXXX"; //numeor de telefono
int estado =8; //Led para ver si el arduino esta en funcionamiento
int bobina =7; //La bobina cerrara el candado
char DAT;
char DAT_dos;
unsigned long age;
char coordenada_gps;
char datosSERIAL[30];
char clave_uno[]= {'B','O','B','O','N'};//Aqui se cambia el mensaje de control
char clave_gps[]= {'G','P','S'};//Aqui se cambia el mensaje de control




void setup() {
  pinMode(bobina,OUTPUT);
  pinMode(estado,OUTPUT);
  //Inicializacion del componente serial
  Serial1.begin(9600);
  Serial.begin(9600);

  delay(2000);
  configuracionInicial();
  Serial.println("Sistema de alarma SIM808 encendida");
  delay(1000);
}

void loop() {
   Serial.println("Esperando recibir mensaje...");
  while(true){
    leer_mensaje();
    }
}


void leer_mensaje(){
  if(Serial1.available()>0){
    char DAT = Serial1.read();
    //El arroba hace detectar el inicio del codigo
    if(DAT == '@'){ 
      digitalWrite(estado,HIGH);//led del testeo del mensaje
      Serial.println("+++Llego el dato+++");

      while(true){
        if(Serial1.available()>0){
          char DAT_dos = Serial1.read();
          datosSERIAL[j] = DAT_dos; //almacena en cadena de caracteres
          j++;
          if(DAT_dos == '\n'){
            Serial.println("+++Verificando codigo y accion a realizar +++");
            Serial.println("Mensaje que llego = ");
            for(int i=0;i<=j;i++){//Imprime todo lo guardado en el array
              Serial.print(datosSERIAL[i]);
              }
            bobina_on();
            gps_on();
            error_de_codigo();
            delay(10);
            digitalWrite(estado,LOW);//apaga el led del verificador
            for(int i =0;i<=j;i++){ //borra los datos del array
              datosSERIAL[i] == 0;
              DAT_dos = 0;
              DAT = 0;
              }
              j=0;
            }
          }
        }
    } 

    
  }
}

void configuracionInicial(){
  Serial.println("configurando... espere");
  delay(2000);
  //CONFIGURACION DE LA VELOCIDAD DEL MODULO
  Serial1.println("AT+IPR=9600");
  Serial.println("AT+IPR=9600");
  delay(100);
  //CONFIGURACION DEL MODO EN TEXTO
  Serial1.println("AT+CMGF=1");
  Serial.println("AT+CMGF=1");
  delay(100);
  //ACTIVAMOS CODIGO PARA ENVIAR MENSAJE
  Serial.println("AT+CMGR=?");
  Serial1.println("AT+CMGR=?");
  delay(100);
  //ACTIVAMOS PARA VER MENSAJES
  Serial1.println("AT+CNMI=2,2,0,0");
  delay(100);
  Serial.println("AT+CNMI=2,2,0,0");
  delay(100);
  Serial.println("Configuracion terminada");
  delay(2000);
  }

void bobina_on(){
    if(datosSERIAL[0] ==clave_uno[0] && datosSERIAL[1] ==clave_uno[1] && datosSERIAL[2] ==clave_uno[2] && datosSERIAL[3] ==clave_uno[3] && datosSERIAL[4] ==clave_uno[4]){
      digitalWrite(bobina,HIGH);
      Serial.println("Candado cerrado");
      digitalWrite(bobina,LOW);
      }
}

void error_de_codigo(){
  if((datosSERIAL[0] == clave_uno[0] && datosSERIAL[1] ==clave_uno[1] && datosSERIAL[2] ==clave_uno[2] && datosSERIAL[3] ==clave_uno[3] && datosSERIAL[4] ==clave_uno[4])|| (datosSERIAL[0] == clave_gps[0] && datosSERIAL[1] ==clave_gps[1] && datosSERIAL[2] ==clave_gps[2])){
    Serial.println("Condigo enviado correcto");
    }
   else{
    Serial.println("Codigo enviado incorrecto");
    }
  }
void gps_on(){
  if(datosSERIAL[0] == clave_gps[0] && datosSERIAL[1] ==clave_gps[1] && datosSERIAL[2] ==clave_gps[2]){
    Serial.println("Codigo correcto gps");
    activacion_gps();
    envio_mensajes_gps_coordenada();
    Serial.println("Lecturra gps enviada al celular");
    lati,longi = 0;
    }
  }

void activacion_gps(){
  //Activo GPS
  Serial1.println("AT+CGNSPWR=1");
  Serial.println("AT+CGNSPWR=1");
  //ACTIVO visualizacion serieal
  Serial1.println("AT+CGNSTST=1");
  Serial.println("AT+CGNSTST=1");
  delay(400);
  Serial.println("estabilizando GPS");
  //esperamos cierto tiempo para que el gps se active
  for(int i=0;i<10;i++){
    delay(1000);
    Serial.print("Tiempo =");
    Serial.println(i);
    }
  Serial.println("Empezando la lectura y conversion");
  tyni_gps_leer(); //leer coordenadas de longitud y latitud
  }

void tyni_gps_leer(){
  int i =0;
  while(i<2){ //lee dos veces las coordenadas
    i++;
  bool newData = false;
  unsigned long chars;
  unsigned short sentence, failed;

  //Por un segundo parseamos la data del GPS
      for(unsigned long start = millis(); millis()-start<1000;){
        while(Serial1.available()){
          char c = Serial.read();
          if(gps.encode(c)){
            newData = true;}
          }
        }

        if(newData){
          float flat, flon;
          unsigned long age;
          gps.f_get_position(&flat,&flon,&age);
          Serial.print("LAT=");
          Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat,6);
          lati = flat;
          Serial.print("LON=");
          Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon,6);
          longi = flon; 
        }
  }
  i=0;
}

void envio_mensajes_gps_coordenada(){
    Serial.print("Datos que se enviaran al celular");
    Serial.print("Latitud:");
    Serial.print(lati,6);
    Serial.print("Longitud:");
    Serial.print(longi,6);
    String latitud = String(lati,6);
    String longitud = String(longi,6);
    String maps = "https://maps.google.com/maps?q=";
    String datos = maps +latitud + "+" +longitud;

    Serial.println(datos);

    Serial1.println("AT+CMGF=1");//modo texto
    delay(1000);
    Serial1.print("AT+CMGS=");
    delay(1000);
    Serial1.print((char)34);
    Serial1.println(numero_cell);
    Serial1.println((char)34);
    delay(1000);
    Serial1.println(datos);
    Serial1.print((char)26);
    delay(1000);
    
  
  }

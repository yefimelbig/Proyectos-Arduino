/*********************************************************
30/11/2022
Trabajo final de Laboratorio - I
Alumnos de primer año de ingenieria en informatica, UBP
Franco Manuel Nicolais
Edgar Karpowicz
Angie Tabares Mendez
Morena Mercado

Contador de alumnos mediante una tarjeta de identificacion.
Al apoyar la tarjeta en el lector RFDI, muestra en un display LCD el nombre del alumno 
y la cantidad de alumnos que apoyaron la tarjeta en el lector.

Uso de librerias:
  - LiquidCrystal I2C por Frank de Brabander, V 1.1.2
  - MFRC552 por GithubCommunity, V 1.4.10
*********************************************************/

//RFDI
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN	9    //Pin 9 para el reset del RC522
#define SS_PIN	10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

byte LecturaUID[4]; 				// crea array para almacenar el UID leido
byte Alumno1[4]= {0xE4, 0xD6, 0x45, 0x28} ;    // Manu Nicolais          UID de tarjeta leido en programa 1
byte Alumno2[4]= {0x63, 0x57, 0x78, 0x3E} ;    // Angie Tabares
byte Alumno3[4]= {0xD9, 0x64, 0x06, 0xB4} ;    // Morena Mercado
byte Alumno4[4]= {0x14, 0x8A, 0x32, 0x2B} ;    // Edgar Karpowicz
byte Alumno5[4]= {0xC3, 0x82, 0x9E, 0x40} ;    // Tomas Molina

//LCD IIC
#include <Wire.h>

#include <LiquidCrystal.h>
#include<LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd (0x27, 16, 2);//creamos un objeto
int cont = 0;
//RGB
int LED = 5;

void setup()
{
//RFDI
  Serial.begin(9600); //Iniciamos la comunicación  serial
	SPI.begin();        //Iniciamos el Bus SPI
	mfrc522.PCD_Init(); // Iniciamos  el MFRC522
	Serial.println("Lectura del UID");

//LCD IIC
  lcd.init(); //inicializamos el lcd 
  lcd.backlight(); //luz de fondo = on 
  lcd.begin(16, 2);
  
  lcd.print("    Hola UBP");//mensaje 1
  lcd.setCursor(0,1);
  lcd.print("   Soy el Pro");
  delay(5000);
  lcd.clear();  //limpia la panralla del lcd
  lcd.print("  Assistance");
  lcd.setCursor(0,1);
  lcd.print("    Keycard");
  delay(5000);
  lcd.clear(); 
  lcd.print("  Estoy listo");
  delay(3000);
  lcd.clear(); 
  lcd.print("Apoye la tarjeta");

//-----RGB-------------
  
  pinMode (LED, OUTPUT);
  
}
//-------------------------------------------------------------------/
void loop()
{
 //--------RFID---------------
// Revisamos si hay nuevas tarjetas  presentes
if ( ! mfrc522.PICC_IsNewCardPresent())		// si no hay una tarjeta presente
    return;						// retorna al loop esperando por una tarjeta
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 		// si no puede obtener datos de la tarjeta
    return;						// retorna al loop esperando por otra tarjeta
    
    Serial.print("UID:");				// muestra texto UID:
    for (byte i = 0; i < mfrc522.uid.size; i++) {	// bucle recorre de a un byte por vez el UID
      if (mfrc522.uid.uidByte[i] < 0x10){		// si el byte leido es menor a 0x10
        Serial.print(" 0");				// imprime espacio en blanco y numero cero
        }
        else{						// sino
          Serial.print(" ");				// imprime un espacio en blanco
          }
          Serial.print(mfrc522.uid.uidByte[i], HEX);   	// imprime el byte del UID leido en hexadecimal
          LecturaUID[i]=mfrc522.uid.uidByte[i];   	// almacena en array el byte del UID leido      
          }
          
          Serial.print("\t");   			// imprime un espacio de tabulacion             
                    
          if(comparaUID(LecturaUID, Alumno1)){		// llama a funcion comparaUID con Usuario1
          cont++;
            Serial.println("Manu Nicolais Presente");	// si retorna verdadero muestra texto bienvenida
            lcd.clear(); 
            digitalWrite(LED,HIGH);
            delay(500);
            digitalWrite(LED,LOW);
            lcd.print("Nicolais F.");
            lcd.setCursor(0,1);
            lcd.print("Presente / A: ");
            lcd.print(cont);}

          else if(comparaUID(LecturaUID, Alumno2)){	// llama a funcion comparaUID con Usuario2
          cont++;
            Serial.println("Angie Tabares Presente");	// si retorna verdadero muestra texto bienvenida
            lcd.clear(); 
            digitalWrite(LED,HIGH);
            delay(500);
            digitalWrite(LED,LOW);
            lcd.print("Tabares A.");
            lcd.setCursor(0,1);
            lcd.print("Presente / A: ");
            lcd.print(cont);}

          else if(comparaUID(LecturaUID, Alumno3)){	// llama a funcion comparaUID con Usuario3
          cont++;
            Serial.println("Morena Mercado Presente");	// si retorna verdadero muestra texto bienvenida
            lcd.clear(); 
            digitalWrite(LED,HIGH);
            delay(500);
            digitalWrite(LED,LOW);
            lcd.print("Mercado M.");
            lcd.setCursor(0,1);
            lcd.print("Presente / A: ");
            lcd.print(cont);}

          else if(comparaUID(LecturaUID, Alumno4)){	// llama a funcion comparaUID con Usuario4
          cont++;
            Serial.println("Edgar Karpowicz Presente");	// si retorna verdadero muestra texto bienvenida
            lcd.clear(); 
            digitalWrite(LED,HIGH);
            delay(500);
            digitalWrite(LED,LOW);
            lcd.print("Karpowicz E.");
            lcd.setCursor(0,1);
            lcd.print("Presente / A: ");
            lcd.print(cont);}

          else if(comparaUID(LecturaUID, Alumno5)){	// llama a funcion comparaUID con Usuario5
          cont++;
            Serial.println("Molina Tomas Presente");	// si retorna verdadero muestra texto bienvenida
            lcd.clear(); 
            digitalWrite(LED,HIGH);
            delay(500);
            digitalWrite(LED,LOW);
            lcd.print("Molina T.");
            lcd.setCursor(0,1);
            lcd.print("Presente / A: ");
            lcd.print(cont);}
            
           else	{					// si retorna falso
            Serial.println("No te conozco"); 		// muestra texto equivalente a acceso denegado    
            lcd.clear(); 
            digitalWrite(LED,HIGH);
            delay(250);
            digitalWrite(LED,LOW);
            delay(250);
            digitalWrite(LED,HIGH);
            delay(250);
            digitalWrite(LED,LOW);
            lcd.print("No te conozco");}      
                  
                  mfrc522.PICC_HaltA();  		// detiene comunicacion con tarjeta                
}

boolean comparaUID(byte lectura[],byte Alumno[])	// funcion comparaUID
{
  for (byte i=0; i < mfrc522.uid.size; i++){		// bucle recorre de a un byte por vez el UID
  if(lectura[i] != Alumno[i])				// si byte de UID leido es distinto a usuario
    return(false);					// retorna falso
  }
  return(true);						// si los 4 bytes coinciden retorna verdadero
}
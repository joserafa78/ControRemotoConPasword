#include <Arduino.h>
#line 1 "c:\\Users\\HELMAN\\Desktop\\ControRemotoConPasword\\ContRemotoInfrarojo.ino"
/*Controlar por Control remoto cinco actuadores en la salida (5,6,7,8,9) pero Antes
se debe digitar el Pasword de 4 digitos, de lo contrario Activa una luz Roja, Indicando Clave Errado, Espere 3 Seg.
En caso de Acertar la Clave, enciende un Led Azul y contara con 10 Segundos para
Activar o desactivar los actuadores, posterior a 10 sg el sistema se volvera a Bloquear.*/

// LED ROJO: Clave Errada, espere 3 Segun
// LED AZUL: Clave Aceptada, Cuenta con 10 Segundos.

// Github: @joserafa78
#include <IRremote.h> // importa libreria IRremote
#define Boton_Pow 0xFFA25D
#define Boton_incre 0xFF906F
#define Boton_decre 0xFFA857
#define Boton_silencio 0xFFE21D
#define Boton_mode 0xFF629D
#define Boton_1 0xFF30CF
#define Boton_2 0xFF18E7
#define Boton_3 0xFF7A85
#define Boton_4 0xFF10EF
#define Boton_5 0xFF38C7
#define Boton_6 0xFF5AA5
#define Boton_7 0xFF42BD
#define Boton_8 0xFF4AB5
#define Boton_9 0xFF52AD
#define Boton_0 0xFF6897

int SENSOR = 11;       // sensor KY-022 a pin digital 11
IRrecv irrecv(SENSOR); // establece al 11 para objeto irrecv
decode_results codigo; // crea objeto codigo de la clase decode_results

int LEDROJO = 2;  // componente rojo de LED RGB a pin 2
int LEDVERDE = 3; // componente verde de LED RGB a pin 3
int LEDAZUL = 4;  // componente azul de LED RGB a pin 4
char DATO[4];
char PSWD[4] = {'1', '1', '2', '2'}; // Pasword
int ESTADO = 0;                      // El Password ha sido aceptado(1) o rechazao(0)
int C = 0;
long ultimotiempo = 0;
long tiempo;
#line 40 "c:\\Users\\HELMAN\\Desktop\\ControRemotoConPasword\\ContRemotoInfrarojo.ino"
void setup();
#line 53 "c:\\Users\\HELMAN\\Desktop\\ControRemotoConPasword\\ContRemotoInfrarojo.ino"
void loop();
#line 40 "c:\\Users\\HELMAN\\Desktop\\ControRemotoConPasword\\ContRemotoInfrarojo.ino"
void setup()
{
    Serial.begin(9600);        // inicializa comunicacion serie a 9600 bps
    irrecv.enableIRIn();       // inicializa recepcion de datos
    pinMode(LEDROJO, OUTPUT);  // pin 2 como salida
    pinMode(LEDVERDE, OUTPUT); // pin 3 como salida
    pinMode(LEDAZUL, OUTPUT);  // pin 4 como salida
    pinMode(5, OUTPUT);        // pin 5 como salida
    pinMode(6, OUTPUT);        // pin 6 como salida
    pinMode(4, OUTPUT);        // pin 7 como salida
    pinMode(8, OUTPUT);        // pin 8 como salida
    pinMode(9, OUTPUT);        // pin 9 como salida
}
void loop()
{
    if (irrecv.decode(&codigo)) // si existen datos ya decodificados
    {
        if ((codigo.value == Boton_1) && (ESTADO == 0))
        {
            DATO[C] = '1';
            C++;
        }
        if ((codigo.value == Boton_2) && (ESTADO == 0))
        {
            DATO[C] = '2';
            C++;
        }
        if ((codigo.value == Boton_3) && (ESTADO == 0))
        {
            DATO[C] = '3';
            C++;
        }
        if ((codigo.value == Boton_4) && (ESTADO == 0))
        {
            DATO[C] = '4';
            C++;
        }
        if ((codigo.value == Boton_5) && (ESTADO == 0))
        {
            DATO[C] = '5';
            C++;
        }
        if ((codigo.value == Boton_6) && (ESTADO == 0))
        {
            DATO[C] = '6';
            C++;
        }
        if ((codigo.value == Boton_7) && (ESTADO == 0))
        {
            DATO[C] = '7';
            C++;
        }
        if ((codigo.value == Boton_8) && (ESTADO == 0))
        {
            DATO[C] = '8';
            C++;
        }
        if ((codigo.value == Boton_9) && (ESTADO == 0))
        {
            DATO[C] = '9';
            C++;
        }
        if ((codigo.value == Boton_0) && (ESTADO == 0))
        {
            DATO[C] = '0';
            C++;
        }
        //================================ACTIVA ACTUADORES================================
        if ((codigo.value == Boton_1) && (ESTADO == 1))
        {
            digitalWrite(5, !digitalRead(5)); // enciende o apaga Salida 5
        }
        if ((codigo.value == Boton_2) && (ESTADO == 1))
        {
            digitalWrite(6, !digitalRead(6)); // enciende o apaga Salida 6
        }
        if ((codigo.value == Boton_3) && (ESTADO == 1))
        {
            digitalWrite(7, !digitalRead(7)); // enciende o apaga Salida 7
        }
        if ((codigo.value == Boton_4) && (ESTADO == 1))
        {
            digitalWrite(8, !digitalRead(8)); // enciende o apaga Salida 8
        }
        if ((codigo.value == Boton_5) && (ESTADO == 1))
        {
            digitalWrite(9, !digitalRead(9)); // enciende o apaga Salida 9
        }
        //=====================================================================================
        if (C > 3)
        {
            if (DATO[0] == PSWD[0] && DATO[1] == PSWD[1] && DATO[2] == PSWD[2] && DATO[3] == PSWD[3])
            {
                Serial.println("CLAVE ACEPTADA..");
                ESTADO = 1;
                digitalWrite(LEDAZUL, !digitalRead(LEDAZUL)); // enciende o apaga componente azul
                tiempo = millis();
                ultimotiempo = tiempo;
                Serial.println(ultimotiempo);
                C = 0;
            }
            else
            {
                Serial.println("Error vuelva de nuevo.");
                ESTADO = 0;
                digitalWrite(LEDROJO, !digitalRead(LEDROJO)); // enciende o apaga componente azul
                delay(3000);
                digitalWrite(LEDROJO, !digitalRead(LEDROJO)); // enciende o apaga componente azul
                C = 0;
            }
        }
        irrecv.resume(); // resume la adquisicion de datos
    }

    tiempo = millis();
    if ((tiempo - ultimotiempo > 10000) && ESTADO == 1) // Pregunta por el tiempo transcurrio en Activacion.
    {
        digitalWrite(LEDAZUL, LOW);  // apaga componente azul
        digitalWrite(LEDROJO, LOW);  // apaga componente rojo
        digitalWrite(LEDVERDE, LOW); // apaga componente verde
        ESTADO = 0;
        C = 0;
    }
    delay(100); // breve demora de 100 ms.
}

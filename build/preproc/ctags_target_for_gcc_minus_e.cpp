# 1 "c:\\Users\\HELMAN\\Desktop\\ControRemotoConPasword\\ContRemotoInfrarojo.ino"
/*Controlar por Control remoto cinco actuadores en la salida (5,6,7,8,9) pero Antes

se debe digitar el Pasword de 4 digitos, de lo contrario Activa una luz Roja, Indicando Clave Errado, Espere 3 Seg.

En caso de Acertar la Clave, enciende un Led Azul y contara con 10 Segundos para

Activar o desactivar los actuadores, posterior a 10 sg el sistema se volvera a Bloquear.*/
# 6 "c:\\Users\\HELMAN\\Desktop\\ControRemotoConPasword\\ContRemotoInfrarojo.ino"
// LED ROJO: Clave Errada, espere 3 Segun
// LED AZUL: Clave Aceptada, Cuenta con 10 Segundos.

// Github: @joserafa78
# 11 "c:\\Users\\HELMAN\\Desktop\\ControRemotoConPasword\\ContRemotoInfrarojo.ino" 2
# 27 "c:\\Users\\HELMAN\\Desktop\\ControRemotoConPasword\\ContRemotoInfrarojo.ino"
int SENSOR = 11; // sensor KY-022 a pin digital 11
IRrecv irrecv(SENSOR); // establece al 11 para objeto irrecv
decode_results codigo; // crea objeto codigo de la clase decode_results

int LEDROJO = 2; // componente rojo de LED RGB a pin 2
int LEDVERDE = 3; // componente verde de LED RGB a pin 3
int LEDAZUL = 4; // componente azul de LED RGB a pin 4
char DATO[4];
char PSWD[4] = {'1', '1', '2', '2'}; // Pasword
int ESTADO = 0; // El Password ha sido aceptado(1) o rechazao(0)
int C = 0;
long ultimotiempo = 0;
long tiempo;
void setup()
{
    Serial.begin(9600); // inicializa comunicacion serie a 9600 bps
    irrecv.enableIRIn(); // inicializa recepcion de datos
    pinMode(LEDROJO, 0x1); // pin 2 como salida
    pinMode(LEDVERDE, 0x1); // pin 3 como salida
    pinMode(LEDAZUL, 0x1); // pin 4 como salida
    pinMode(5, 0x1); // pin 5 como salida
    pinMode(6, 0x1); // pin 6 como salida
    pinMode(4, 0x1); // pin 7 como salida
    pinMode(8, 0x1); // pin 8 como salida
    pinMode(9, 0x1); // pin 9 como salida
}
void loop()
{
    if (irrecv.decode(&codigo)) // si existen datos ya decodificados
    {
        if ((codigo.value == 0xFF30CF) && (ESTADO == 0))
        {
            DATO[C] = '1';
            C++;
        }
        if ((codigo.value == 0xFF18E7) && (ESTADO == 0))
        {
            DATO[C] = '2';
            C++;
        }
        if ((codigo.value == 0xFF7A85) && (ESTADO == 0))
        {
            DATO[C] = '3';
            C++;
        }
        if ((codigo.value == 0xFF10EF) && (ESTADO == 0))
        {
            DATO[C] = '4';
            C++;
        }
        if ((codigo.value == 0xFF38C7) && (ESTADO == 0))
        {
            DATO[C] = '5';
            C++;
        }
        if ((codigo.value == 0xFF5AA5) && (ESTADO == 0))
        {
            DATO[C] = '6';
            C++;
        }
        if ((codigo.value == 0xFF42BD) && (ESTADO == 0))
        {
            DATO[C] = '7';
            C++;
        }
        if ((codigo.value == 0xFF4AB5) && (ESTADO == 0))
        {
            DATO[C] = '8';
            C++;
        }
        if ((codigo.value == 0xFF52AD) && (ESTADO == 0))
        {
            DATO[C] = '9';
            C++;
        }
        if ((codigo.value == 0xFF6897) && (ESTADO == 0))
        {
            DATO[C] = '0';
            C++;
        }
        //================================ACTIVA ACTUADORES================================
        if ((codigo.value == 0xFF30CF) && (ESTADO == 1))
        {
            digitalWrite(5, !digitalRead(5)); // enciende o apaga Salida 5
        }
        if ((codigo.value == 0xFF18E7) && (ESTADO == 1))
        {
            digitalWrite(6, !digitalRead(6)); // enciende o apaga Salida 6
        }
        if ((codigo.value == 0xFF7A85) && (ESTADO == 1))
        {
            digitalWrite(7, !digitalRead(7)); // enciende o apaga Salida 7
        }
        if ((codigo.value == 0xFF10EF) && (ESTADO == 1))
        {
            digitalWrite(8, !digitalRead(8)); // enciende o apaga Salida 8
        }
        if ((codigo.value == 0xFF38C7) && (ESTADO == 1))
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
        digitalWrite(LEDAZUL, 0x0); // apaga componente azul
        digitalWrite(LEDROJO, 0x0); // apaga componente rojo
        digitalWrite(LEDVERDE, 0x0); // apaga componente verde
        ESTADO = 0;
        C = 0;
    }
    delay(100); // breve demora de 100 ms.
}

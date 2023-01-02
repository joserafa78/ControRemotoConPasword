#include <IRremote.h> // importa libreria IRremote

int SENSOR = 11; // sensor KY-022 a pin digital 11
IRrecv irrecv(SENSOR);
decode_results codigo;

void setup()
{
    Serial.begin(9600);
    Serial.println("Escaneando Codigos del Control Remoto:");
    irrecv.enableIRIn(); // inicializa recepcion de datos
}

void loop()
{
    if (irrecv.decode(&codigo))
    {
        Serial.println("Copia y Pega este codigo en un Blog de notas:");
        Serial.println(codigo.value, HEX);
        irrecv.resume();
    }
    delay(100); // demora de 100 ms.
}
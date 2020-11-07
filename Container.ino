#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 Radio(9, 10);

const byte adressess[][6] = {"00001","00002"};

int temporAltitude = 10;
int temporTemper = 11;
int temporPress = 12;
boolean RelayData = false;
int counter = 0;



typedef struct{
    int ALTITUDE ;
    int PRESSURE ;
    int TEMP ;
}SPAYLOAD;


SPAYLOAD SP1DATA;





void setup()
{
    Serial.begin(9600);
    Radio.begin();
    Radio.openWritingPipe(adressess[1]); // 00002
    Radio.openReadingPipe(1, adressess[0]);  // 00001
    Radio.setPALevel(RF24_PA_LOW);
    Radio.setChannel(3);
    
}


void loop()
{
    
    delay(10); // 5 uSecond wait.
    if (RelayData)
    {

        Radio.startListening();
        if (Radio.available())
        {
            Serial.println("Radio available listening...");
            Radio.read(&SP1DATA, sizeof(SP1DATA));
        }
        else
        {
            Serial.println("NOT AVAILABLE..;");
        }
        

    }
    else
    {
    
        
        if (counter == 20 || counter > 20)
        {
            RelayData = true;
            Radio.stopListening();

            Serial.println("SEND DATA COMMAND SENDING...");
            
            // do
            // {
            //     Radio.stopListening();
            //     TRY_TRANSMIT();
            //     Serial.println("Transmit Failed...");
            // } while (!TRY_TRANSMIT());
            
            boolean transmitted = Radio.write(&RelayData, sizeof(RelayData));
            if (transmitted)
            {
                Serial.println("SEND DATA COMMAND COMPLETED....");
                Radio.startListening();
            }
            else
            {
                Serial.println("SEND DATA COMMAND FAILED...");
                RelayData = false;
            }
            
        }
        counter++;

    }
    Serial.println("------------------");
    // Serial.print("Container Temperature : ");
    // Serial.println(temporTemper);
    // Serial.print("Container Pressure : ");
    // Serial.println(temporPress);
    // Serial.print("Container Altitude : ");
    // Serial.println(temporTemper);
    // Serial.print("Relay Data State : ");
    // Serial.println(RelayData);

    Serial.print("SP1 Temp : ");
    Serial.println(SP1DATA.TEMP);
    Serial.print("SP1 Pressure : ");
    Serial.println(SP1DATA.PRESSURE);
    Serial.print("SP1 Altitude :");
    Serial.println(SP1DATA.ALTITUDE);
    Serial.println("------------------");
}

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 Radio(9, 10);


const byte adressess[][6] = {"00001","00002"};
boolean SendData = false;

typedef struct{
    int ALTITUDE ;
    int PRESSURE ;
    int TEMP;
} SPAYLOAD;
SPAYLOAD SP1DATA;


void setup()
{   

    SP1DATA.ALTITUDE = 43;
    SP1DATA.PRESSURE = 44;
    SP1DATA.TEMP = 45;
    Serial.begin(9600);
    Radio.begin();
    Radio.openReadingPipe(1, adressess[1]);
    Radio.openWritingPipe(adressess[0]);
    Radio.setPALevel(RF24_PA_LOW);
    Radio.setChannel(3);
}
void loop()
{
    delay(10);
    if (SendData == false)
    {
        Radio.startListening();
        // if (Radio.available())
        // while (!Radio.available())
        // {
        //     ;
        // }
        // Radio.read(&SendData, sizeof(SendData));
        // delay(10);
        if (Radio.available())  
        {   
            Serial.println("Available Radio Founded.. reading data..");
            Radio.read(&SendData, sizeof(SendData));
            Serial.println("**************************");
            Serial.println(SendData);
            Serial.println("**********************");
            if (SendData)
            {
                
                Radio.stopListening();
            }
            
        }
        else
        {
            Serial.println("Radio is not available...");
        }
        
        
    }
    else
    {
        Serial.println("Data Transfer TRYING...");
        // delay(10);
        Radio.stopListening();
        // do
        // {
        //     Serial.println("TRYINGG TO SEND...");
        //     TRY_SEND_DATA();
        // } while (!TRY_SEND_DATA());
        // Serial.println("SENDING COMPLETED....");
        
        boolean data_transferred = Radio.write(&SP1DATA, sizeof(SP1DATA));
        if (data_transferred)
        {
            Serial.println("DATA TRANSFER COMPLETED.");
        }
        else{
            Serial.println("Data Transfer failed.");
        }
        // Radio.write(&SP1DATA, sizeof(SP1DATA));
    }
    
    // Serial.println("-----------------");
    // Serial.print("SCIENCE PAYLOAD ALTITUDE : ");
    // Serial.println(SP1DATA.ALTITUDE);
    // Serial.print("SCIENCE PAYLOAD PRESSURE: ");
    // Serial.println(SP1DATA.PRESSURE);
    // Serial.print("SCIENCE PAYLOAD TEMPERATURE: ");
    // Serial.println(SP1DATA.TEMP);
    // Serial.println("-----------------");
    
}
/*
  BLE_Peripheral.ino

  This program uses the ArduinoBLE library to set-up an Arduino Nano 33 BLE 
  as a peripheral device and specifies a service and a characteristic. Depending 
  of the value of the specified characteristic, an on-board LED gets on. 

  The circuit:
  - Arduino Nano 33 BLE. 

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>
      

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

int something = -1;
byte i = 0;

BLEService someService(deviceServiceUuid); 
BLEByteCharacteristic someCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);


void setup() {
  Serial.begin(9600);
  while (!Serial);  
  
  if (!BLE.begin()) {
    Serial.println("- Starting BLE module failed!");
    while (1);
  }
  BLE.setLocalName("Arduino Nano 33 BLE (Peripheral)");
  BLE.setAdvertisedService(someService);
  someService.addCharacteristic(someCharacteristic);
  BLE.addService(someService);
  someCharacteristic.writeValue((byte) 1);
  BLE.advertise();

  Serial.println("Nano 33 BLE (Peripheral Device)");
  Serial.println(" ");
}

void loop() {
  BLEDevice central = BLE.central();
  Serial.println("- Discovering central device...");
  delay(500);

  if (central) {
    Serial.println("* Connected to central device!");
    Serial.print("* Device MAC address: ");
    Serial.println(central.address());
    Serial.println(" ");
    Serial.println(someCharacteristic.value());
    someCharacteristic.writeValue((byte) 2);
    Serial.println(someCharacteristic.value());

    while (central.connected()) {
//      writeRegister();
      //i++;
      //Serial.println(someCharacteristic.value());
      //someCharacteristic.writeValue((byte) i);
      if (someCharacteristic.written()) {
         something = someCharacteristic.value();
         Serial.println(something);
         someCharacteristic.writeValue((byte) something+10);
       }
       //delay(1000);
    }
    
    Serial.println("* Disconnected to central device!");
  }
}

//void writeRegister(){
//    i++;
//    someCharacteristic.writeValue(i);
//}

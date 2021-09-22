#include <ArduinoBLE.h>
      

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";


BLEService someService(deviceServiceUuid); 
BLEByteCharacteristic someCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);

int something = -1;


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
  someCharacteristic.writeValue(-1);
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

    while (central.connected()) {
      if (someCharacteristic.written()) {
         something = someCharacteristic.value();
         Serial.println(something);
       }
    }
    
    Serial.println("* Disconnected to central device!");
  }
  
}

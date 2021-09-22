#include <ArduinoBLE.h>

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

byte val=0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  
  if (!BLE.begin()) {
    Serial.println("* Starting BLE module failed!");
    while (1);
  }
  
  BLE.setLocalName("Nano 33 BLE (Central)"); 
  BLE.advertise();

  Serial.println("Arduino Nano 33 BLE Sense (Central Device)");
  Serial.println(" ");
}

void loop() {

  BLEDevice peripheral;
  
  Serial.println("- Discovering peripheral device...");

  do
  {
    BLE.scanForUuid(deviceServiceUuid);
    peripheral = BLE.available();
  } while (!peripheral);
  
  if (peripheral) {
    Serial.println("* Peripheral device found!");
    Serial.print("* Device MAC address: ");
    Serial.println(peripheral.address());
    Serial.print("* Device name: ");
    Serial.println(peripheral.localName());
    Serial.print("* Advertised service UUID: ");
    Serial.println(peripheral.advertisedServiceUuid());
    Serial.println(" ");
    BLE.stopScan();
    controlPeripheral(peripheral);
  }
}

void controlPeripheral(BLEDevice peripheral){
  peripheral.connect();
  peripheral.discoverAttributes();
  BLECharacteristic someCharacteristic = peripheral.characteristic(deviceServiceCharacteristicUuid);
  someCharacteristic.subscribe();
  Serial.println("Connected");
  byte i=0;
  byte j;
    while(peripheral.connected()){
      i++;
      //someCharacteristic.writeValue((byte) i);
      delay(1000);
      someCharacteristic.readValue(j);
      Serial.println(j);
//      if(someCharacteristic.valueUpdated()){
//        byte val;
//        someCharacteristic.readValue(val);
//        Serial.println(val);
//      }
    }
}

#include <FlexCAN.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#include <Fonts/Org_01.h>

#include <Fonts/Picopixel.h>

#define SSD1306_128_64
#define SSD1306_LCDWIDTH 128
#define SSD1306_LCDHEIGHT 64

#define OLED_DC 6
#define OLED_CS 10
#define OLED_RESET 5
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);


#if (SSD1306_LCDHEIGHT != 64)

#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


static CAN_message_t msg;
static CAN_message_t inMsg;
static uint8_t hex[17] = "0123456789abcdef";

static void hexDump(uint8_t dumpLen, uint8_t *bytePtr) {
  uint8_t working;
  while (dumpLen--) {
    working = *bytePtr++;
    Serial.write(hex[working >> 4]);
    Serial.write(hex[working & 15]);
  }
  Serial.write('\r');
  Serial.write('\n');
}




Adafruit_MPU6050 mpu;

//------------------SETUP------------------------------------------

void setup() {
  delay(1000);

  Can0.begin(250000);  //set speed here.
  msg.ext = 0;
  msg.id = 0x555;
  msg.len = 2;
  msg.buf[0] = 00;
  msg.buf[1] = 00;
  msg.buf[2] = 00;
  msg.buf[3] = 00;
  msg.buf[4] = 00;
  msg.buf[5] = 00;
  msg.buf[6] = 00;
  msg.buf[7] = 00;

  //-----------setupdisplay------------------------------------------
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  delay(1000);
  Serial.println(F("CAN Bus Tx test"));


  //-------------setupMPU----------------------------------------------------------------
  Serial.begin(9600);
  while (!Serial)
    delay(10);  // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  Serial.println("");
  delay(100);







  //-------------setupCAN---------

  /* msg.ext = 0;
  msg.id = 0x100;
  msg.len = 8;
  msg.buf[0] = a.acceleration.z;
  msg.buf[1] = 02;
  msg.buf[2] = 03;
  msg.buf[3] = 04;
  msg.buf[4] = 05;
  msg.buf[5] = 06;
  msg.buf[6] = 07;
  msg.buf[7] = 10;
Can0.write(msg);
*/
}

int counter = 0;
sensors_event_t a, g, temp;
void loop() {
  // sensors_event_t a, g, temp;
  //-----------------mpu--------------------------------
  // Get new sensor events with the readings */
  mpu.getEvent(&a, &g, &temp);





  //---------------Serialprint--------------------------
  /*
  // Serial.print("CAN bus 0: "); hexDump(8, msg.buf);
  
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println("");
*/
  delay(500);


  //--------------SENDE MPU over CAN

  while (Can0.available()) {
    Can0.read(inMsg);
    if (inMsg.id == 0x123) {

      while (1) {
        Can0.read(inMsg);
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(10, 6);
        display.clearDisplay();
        display.println("MAS 245 - Gruppe 12");
        display.drawLine(5, 12, 119, 12, WHITE);

        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(5, 18);
        display.println("CAN-statistikk: ");

        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(5, 25);
        display.println("-----------------");

        display.setCursor(5, 30);
        display.println("Antall mottatt: ");

         display.setTextSize(1);
        display.setCursor(95, 30);
        display.print(counter);

        display.setTextSize(1);
        display.setCursor(5, 40);
        display.println("Mottok sist ID: ");

        display.setCursor(95, 40);
        display.print(msg.id - 12);

        display.setCursor(5, 45);
        display.println("-----------------");


        display.setTextSize(1);
        display.setCursor(5, 55);
        display.print("IMU-m");
        display.print(char(134));
        display.print("ling Z:");

        display.setCursor(82, 55);
        display.print(inMsg.buf[0]);



        display.drawRoundRect(0, 0, 128, 64, 5, WHITE);
        display.display();
       // display.setFont(&Picopixel);
        display.setCursor(115, 47);
        display.print("m");

        //display.setCursor(110, 49);
          display.drawLine(110, 54, 130, 54,
                        WHITE);

        display.setCursor(110, 55);
        display.print("s^2");

        //display.clearDisplay();
        display.display();

        float b = abs(a.acceleration.z);
        int fTall = floor(b);
        float c = b - fTall;
        int aTall = 100 * c;
        msg.buf[0] = fTall;
        msg.buf[1] = aTall;
        //msg.buf[2] = a.acceleration.z;
        Can0.write(msg);

        counter++;
        delay(995);
      }
    }
  }






  //--------------CAN------------------------
  /* Print out the values */
  float b = a.acceleration.z;
  int fTall = floor(b);
  float c = b - fTall;
  int aTall = 100 * c;
  msg.buf[0] = fTall;
  msg.buf[1] = aTall;
  msg.buf[2] = a.acceleration.z;





















  //-------OLED---------------------------

  display.setTextSize(0);
  display.setTextColor(WHITE);
  display.setCursor(10, 4);
  display.clearDisplay();
  display.println("MAS 245 - Gruppe 12");
  display.drawLine(5, 12, 119, 12, WHITE);

  display.setTextSize(0);
  display.setTextColor(WHITE);
  display.setCursor(5, 18);
  display.println("CAN-statistikk: ");
  display.setTextSize(0);
  display.setTextColor(WHITE);
  display.setCursor(5, 25);
  display.println("-------------------");
  display.setCursor(5, 30);
  display.println("Antall mottatt: ");
  display.setCursor(90, 30);
  display.print(" 11 ");
  display.setCursor(5, 40);
  display.println("Mottok sist ID: ");
  display.setCursor(90, 40);
  //display.print(" TALL ");
  display.print(" 555 ");
  display.setCursor(5, 45);
  display.println("-------------------");
  display.setCursor(5, 55);
  display.print("IMU-m");
  display.print(char(134));
  display.print("ling Z:");
  display.setCursor(82, 55);
  //display.print(a.acceleration.z);
  display.print("14");

  display.drawRoundRect(0, 0, 128, 64, 5, WHITE);

  display.display();
}
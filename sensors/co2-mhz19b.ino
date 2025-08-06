/*----------------------------------------------------------
    MH-Z19 CO2 sensor  SAMPLE
  ----------------------------------------------------------*/

#include "MHZ19.h"

// rx & tx nya kebalik 
const int rx_pin = 13; //Serial rx pin no - D7 Wemos D1 mini
//const int tx_pin = 15; //Serial tx pin no D8 Wemos D1 mini
const int tx_pin = 16; //Serial tx pin no - D0 Wemos D1 mini

const int pwmpin = 14; // D5 Wemos D1 mini

MHZ19 *mhz19_uart = new MHZ19(rx_pin,tx_pin);
MHZ19 *mhz19_pwm = new MHZ19(pwmpin);

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup()
{
    Serial.begin(115200);
    mhz19_uart->begin(rx_pin, tx_pin);
    mhz19_uart->setAutoCalibration(false);
    delay(3000);
    Serial.print("MH-Z19 now warming up...  status:");
    Serial.println(mhz19_uart->getStatus());
    delay(1000);
}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
void loop()
{
    measurement_t m = mhz19_uart->getMeasurement();

    Serial.print("co2: ");
    Serial.println(m.co2_ppm);
    Serial.print("temp: ");
    Serial.println(m.temperature);

// sering tidak jalan - tidak reliable
//    int co2ppm = mhz19_pwm->getPpmPwm();
//    Serial.print("co2pwm: ");
//    Serial.println(co2ppm);

    Serial.println("----- sleeping 5 seconds");
    
    delay(5000);
}



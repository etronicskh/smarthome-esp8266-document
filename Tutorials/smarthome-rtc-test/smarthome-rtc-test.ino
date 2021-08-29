/*
 * Library: https://www.arduino.cc/reference/en/libraries/rtc-by-makuna/
 */

#include <ThreeWire.h>  
#include <RtcDS1302.h>

#define RTC_IO  D7 //
#define RTC_CLK D5 //
#define RTC_CE  D0 //

#define SET_DATE_TIME 0 // set this to "true" when you want to update time and date

ThreeWire myWire(D7,D5,D0); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void setup () 
{
    Serial.begin(115200);

    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();
    if(SET_DATE_TIME) Rtc.SetDateTime(compiled);  // Set time and date from compiled value
}

void loop ()
{
    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();

    if (!now.IsValid())
    {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }

    delay(10000); // ten seconds
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}

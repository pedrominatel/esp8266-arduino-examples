#include <Ticker.h>
Ticker tickerOSWatch;

#define OSWATCH_RESET_TIME 30

static unsigned long last_loop;

void ICACHE_RAM_ATTR osWatch(void) {
    unsigned long t = millis();
    unsigned long last_run = abs(t - last_loop);
    if(last_run >= (OSWATCH_RESET_TIME * 1000)) {
        ESP.restart();  // normal reboot
        //ESP.reset();  // hard reset
    }
}

void setup() {

   Serial.begin(115200);
   last_loop = millis();
   tickerOSWatch.attach_ms(((OSWATCH_RESET_TIME / 3) * 1000), osWatch);
   Serial.println("Boot!!");
}

void wdt_kick(void) {
   last_loop = millis();
}

void loop() {
   wdt_kick();
   while(1)   delay(1000);  // this will trigger the os watch
}

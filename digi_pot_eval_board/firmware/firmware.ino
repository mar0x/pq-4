
#if defined(ARDUINO)

#include "controller.h"

void setup(void) {
    pq4::controller_.setup();
}

void loop(void) {
    pq4::controller_.loop();
}

#endif

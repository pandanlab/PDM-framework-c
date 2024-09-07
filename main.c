#include <stdint.h>
#include "software/layer_integration/int_blink1/int_blink1.h"


int main(){
    blink_config();
    while (1) blink_led();
    return 0;
}

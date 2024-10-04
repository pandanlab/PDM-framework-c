#include "../../../software/layer_integration/int_blink/int_blink.h"

int main(){
    configBlink();
    while (1)
    {
        executionBlink();
    }
    return 0;
}
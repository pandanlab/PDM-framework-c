#include "hardware/stm32f103c8t6/driver/uart/uart.h"
#include "software/layer_unit/unit_delay/unit_delay.h"

void uart_printf(uint8_t * buffer){
  int i = 0;
  while(1){
    uint8_t data = buffer[i];
    uart_write(USART1,data);
    if(data == 0) break;
    i++;
  }
}

void uart_readString(uint8_t * buffer, uint8_t size){
  for(int i = 0; i < size; i++){
    uint8_t data = uart_read(USART1);
    buffer[i] = data;
  }

}

int main(){
  //initialized 
  rcc_apb2_enable(APB2_GPIOA);
  rcc_apb2_enable(APB2_USART1);
  uart_init(USART1,GPIOA,PIN_9,PIN_10);

  uint8_t buffer_dataWrite[] = "hello world\r\n";

  uart_printf(&buffer_dataWrite[0]);
  //execution
  while(1){
    while (uart_statusRead(USART1)==1)
    {
      uart_readString(&buffer_dataWrite[0],5);
      uart_printf(&buffer_dataWrite[0]);
      uart_resetRead(USART1);
    }
  }
  return 0;
}
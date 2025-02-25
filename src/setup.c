#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "ssd1306.h"
#include "font.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C




void init_display(ssd1306_t *ssd) {
    // Inicializa o display usando o ponteiro passado como argumento
    ssd1306_init(ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); 
    ssd1306_config(ssd);  
    ssd1306_send_data(ssd); 

    // Limpa o display
    ssd1306_fill(ssd, false);
    ssd1306_send_data(ssd);
}

/*
* Função para inicializar o display
*/
void setup_display() {
    
    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);
  
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line
   
  
  }


/*
* Função para inicializar os botões
*/
void setup_botoes(uint pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
  }


void setup_joystick(uint pino_vrx, uint pino_vry, uint pino_sw) {
  adc_init();
  adc_gpio_init(pino_vrx);
  adc_gpio_init(pino_vry);
  gpio_init(pino_sw);
  gpio_set_dir(pino_sw, GPIO_IN);
  gpio_pull_up(pino_sw);
}


void setup_led(uint pino) {
  gpio_init(pino);
  gpio_set_dir(pino, GPIO_OUT);
  gpio_put(pino, 0);
}
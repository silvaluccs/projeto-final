#include "hardware/i2c.h"
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
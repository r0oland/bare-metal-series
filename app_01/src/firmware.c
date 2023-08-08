#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define LED_PIN  GPIO8
#define LED_PORT GPIOA

static void this_rcc_setup(void) {
  rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);
}

static void this_gpio_setup(void) {
  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
}

static void delay_cycles(uint32_t cycles) {
  volatile uint32_t i;
  for (i = 0; i < cycles; i++) {
    __asm__("nop");
  }
}

int main(void) {

  this_rcc_setup();
  this_gpio_setup();

  while (1) {
    gpio_toggle(GPIOA, LED_PIN);
    delay_cycles(8400000 / 4);
  }

  return 0;
}

/*******************************************************************
 * @file main.c
 *
 * @brief Main file.
 * @author João Matheus Nascimento Dias (jmnd@ic.ufal.br)
 * @author José Félix de Oliveira Neto (jfon@ic.ufal.br)
 * @version 0.1
 * @date 26/08/2026
 *******************************************************************/

#include <zephyr/drivers/gpio/gpio_emul.h>
#include <zephyr/drivers/led.h>
#include <zephyr/kernel.h>

#include "board_io.h"

static const struct gpio_dt_spec btn = GPIO_DT_SPEC_GET(BUTTON_NODE, gpios);

int main(void)
{

	int ret;
	int btn_state;

	ret = io_init();
	if (ret < 0) {
		printk("Could not initialize gpios: %d\r\n", ret);
		return ret;
	}

	int button_states[] = {0, 1, 0, 1};

	for (int i = 0; i < 4; i++) {
		ret = gpio_emul_input_set_dt(&btn, button_states[i]);
		if (ret < 0) {
			printk("Could not set button state: %d\r\n", ret);
			return ret;
		}

		btn_state = button_read();
		if (btn_state < 0) {
			printk("Could not read button state: %d\r\n", btn_state);
			return btn_state;
		}

		printk("Button: %d -> ", btn_state);

		ret = led_set(btn_state);
		if (ret < 0) {
			printk("Could not set led: %d\r\n", ret);
			return ret;
		}
		printk("\n");
	}

	return 0;
}

#include "board_io.h"
#include <stdbool.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/led.h>

static const struct led_dt_spec led = LED_DT_SPEC_GET(LED0_NODE);
static const struct gpio_dt_spec btn = GPIO_DT_SPEC_GET(BUTTON_NODE, gpios);

int io_init(void)
{
	int ret;

	if (!led_is_ready_dt(&led)) {
		printk("Led is not ready\r\n");
		return -ENODEV;
	}

	/* Led starts off */
	ret = led_off_dt(&led);
	if (ret < 0) {
		printk("Could not configure led: %d\r\n", ret);
		return ret;
	}

	if (!gpio_is_ready_dt(&btn)) {
		printk("Button is not ready: %d\r\n", ret);
		return -ENODEV;
	}

	ret = gpio_pin_configure_dt(&btn, GPIO_INPUT);
	if (ret < 0) {
		printk("Can not configure button gpio: %d\r\n", ret);
		return ret;
	}

	return 0;
}

int led_set(bool on)
{
	int ret;

	if (on) {
		ret = led_on_dt(&led);

		if (ret < 0) {
			printk("Could not turn on led: %d\r\n", ret);
			return ret;
		}
		printk("LED: 1");
	} else {
		ret = led_off_dt(&led);

		if (ret < 0) {
			printk("Could not turn off led: %d\r\n", ret);
			return ret;
		}
		printk("LED: 0");
	}

	return 0;
}

int button_read(void)
{
	return gpio_pin_get_dt(&btn);
}
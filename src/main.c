/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 500

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)
#define BUTTON0_NODE DT_ALIAS(sw0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec ledA = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec ledB = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec ledC = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec ledD = GPIO_DT_SPEC_GET(LED3_NODE, gpios);
static const struct gpio_dt_spec bt0 = GPIO_DT_SPEC_GET(BUTTON0_NODE, gpios);

int main(void)
{
	int ret;

	if ((!gpio_is_ready_dt(&ledA)) | (!gpio_is_ready_dt(&ledB)) | (!gpio_is_ready_dt(&ledC)) | (!gpio_is_ready_dt(&ledD)) | (!gpio_is_ready_dt(&bt0)))
	{
		return 0;
	}

	ret = gpio_pin_configure_dt(&ledA, GPIO_OUTPUT_ACTIVE);
	if (ret < 0)
	{
		return 0;
	}
	ret = gpio_pin_configure_dt(&ledB, GPIO_OUTPUT_ACTIVE);
	if (ret < 0)
	{
		return 0;
	}
	ret = gpio_pin_configure_dt(&ledC, GPIO_OUTPUT_ACTIVE);
	if (ret < 0)
	{
		return 0;
	}
	ret = gpio_pin_configure_dt(&ledD, GPIO_OUTPUT_ACTIVE);
	if (ret < 0)
	{
		return 0;
	}
	ret = gpio_pin_configure_dt(&bt0, GPIO_INPUT);
	if (ret < 0)
	{
		return 0;
	}

	while (1)
	{
		if (!gpio_pin_get_dt(&bt0))
		{
			ret = gpio_pin_toggle_dt(&ledA);
			ret = gpio_pin_toggle_dt(&ledB);
			ret = gpio_pin_toggle_dt(&ledC);
			ret = gpio_pin_toggle_dt(&ledD);
		}

		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}


#include "zephyr/device.h"
#include "zephyr/sys/printk.h"
#include <stdio.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/kernel.h>




/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 3000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)


/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);


int main(void) {
  int ret;
  bool led_state = true;

  if (!gpio_is_ready_dt(&led)) {
    return 0;
  }

  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
  if (ret < 0) {
    return 0;
  }

  /*I2c*/ 
  //use device ready to check device 
  // const struct device *vl53ldk_dev = device_get_binding("VL53LDK");
  // if (!vl53ldk_dev) {
  //     printf("Failed to get VL53LDK device \n");
  //     return 0;
  // }
  // printf("got VL53LDK device \n");

  // uint8_t reg_addr = 0xC0;
  // uint8_t reg_value;

  // ret = i2c_write_read(vl53ldk_dev, 0x52, &reg_addr, sizeof(reg_addr), &reg_value, sizeof(reg_value));
  
  // if (ret != 0) {
  //    printf("I2C write_read failed with error %d\n", ret);
  // } else {
  //    printf("Data read: 0x%02x \n", reg_value);
  // }

   
  /*End I2c */

  while (1) {
    ret = gpio_pin_toggle_dt(&led);
    if (ret < 0) {
      return 0;
    }

    led_state = !led_state;
    printk("LED state: %s\n", led_state ? "ON" : "OFF");
    k_msleep(SLEEP_TIME_MS);
  }
  return 0;
}


// Código de lectura de temperatura del sensor LSM6DSV16X


#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <stdlib.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>

// VERSION SIN DRIVER

// DEFINICIONES

// I2C Device Address 8 bit format  if SA0=0 -> D5 if SA0=1 -> D7 
#define LSM6DSV16X_I2C_ADD_L    0xD5U
#define LSM6DSV16X_I2C_ADD_H    0xD7U
#define LSM6DSV16X_I2C_ADDR 	0x6A
#define LSM6DSV16X_ID           0x70U // who am i

// LOW ADDRESSES Gyros and Accel
#define OUTX_L_G 				0x22 
#define OUTY_L_G 				0x24
#define OUTZ_L_G 				0x26
#define OUTX_L_A 				0x28
#define OUTY_L_A 				0x2A
#define OUTZ_L_A 				0x2C

#define CTRL_ACC				0x10
#define CTRL_GYR				0x11

#define CONF_CTRL_ACC			0x72
#define CONF_CTRL_GYR			0x52


// Operación

#define I2C_NODE DT_NODELABEL(i2c0)
static const struct device *i2c_dev = DEVICE_DT_GET(I2C_NODE);


static uint8_t i2c_buffer[2];  
static uint8_t i2c_write_buffer[4]; // buffer para escrituras
static uint8_t i2c_read_buffer[2];  // buffer para lecturas
static uint8_t i2c_read_buffer2[2]; 
static uint8_t i2c_read_buffer3[2]; 

int main(void) // void
{
	int err;

	if (!i2c_dev) {
        printk("I2C: Device not found.\n");
        return;
    }

	//gpio_pin_set_dt(&enable_i2c, 1); // alto
	int i = 0;
	while (true)
	{
		i2c_buffer[0] = 0x0F;
		 
		
			// READ DEVICE ID
		i2c_buffer[0] = 0x0F;
		err = i2c_read(i2c_dev, i2c_buffer, 2, 0x6A); 
		if (err < 0){printk(" Sin enlace ");break;} 

			// ACC CONFIG
		i2c_write_buffer[0] = CTRL_ACC;
		i2c_write_buffer[1] = CONF_CTRL_ACC;
        err = i2c_write(i2c_dev, i2c_write_buffer, 2, 0x0F); 
        if (err < 0) {printk("CON ENLACE !! \n");return;}
		else {printk("Acc config success \n");}

			// GYR CONFIG
		i2c_write_buffer[0] = CTRL_GYR;
		i2c_write_buffer[1] = CONF_CTRL_GYR;
        err = i2c_write(i2c_dev, i2c_write_buffer, 2, 0x6B);
        if (err < 0) {printk("Error gyr config \n");return;}
		else {printk("Config success \n");}

			// ACC READING
		i2c_write_buffer[0] = OUTX_L_A;
        err = i2c_write_read(i2c_dev, LSM6DSV16X_I2C_ADDR,i2c_write_buffer, 1, i2c_read_buffer, 2);
            
		i2c_write_buffer[0] = OUTY_L_A;
        err = i2c_write_read(i2c_dev, LSM6DSV16X_I2C_ADDR,i2c_write_buffer, 1, i2c_read_buffer2, 2);

		i2c_write_buffer[0] = OUTZ_L_A;
        err = i2c_write_read(i2c_dev, LSM6DSV16X_I2C_ADDR,i2c_write_buffer, 1, i2c_read_buffer3, 2);
        if (err < 0) {printk("Accel reading error \n");return;}
		else {0;}

		printk("\n Accel raw (hex):   0x%02X; 0x%02X; 0x%02X <-----\n", i2c_read_buffer3[0], i2c_read_buffer2[0], i2c_read_buffer[0]);

		float accel_x = sensor_value_to_double(i2c_read_buffer[0]);
		float accel_y = sensor_value_to_double(i2c_read_buffer2[0]);
		float accel_z = sensor_value_to_double(i2c_read_buffer3[0]);

			// GYRO READING
		i2c_write_buffer[0] = OUTX_L_G;
        err = i2c_write_read(i2c_dev, LSM6DSV16X_I2C_ADDR,i2c_write_buffer, 1, i2c_read_buffer, 2);
            
		i2c_write_buffer[0] = OUTY_L_G;
        err = i2c_write_read(i2c_dev, LSM6DSV16X_I2C_ADDR,i2c_write_buffer, 1, i2c_read_buffer2, 2);

		i2c_write_buffer[0] = OUTZ_L_G;
        err = i2c_write_read(i2c_dev, LSM6DSV16X_I2C_ADDR,i2c_write_buffer, 1, i2c_read_buffer3, 2);
        if (err < 0) {printk("Accel reading error \n");return;}
		else {0;}

		printk("\n Gyro raw (hex):   0x%02X; 0x%02X; 0x%02X <-----\n", i2c_read_buffer3[0], i2c_read_buffer2[0], i2c_read_buffer[0]);

		float gyro_x = sensor_value_to_double(i2c_read_buffer[0]);
		float gyro_y = sensor_value_to_double(i2c_read_buffer2[0]);
		float gyro_z = sensor_value_to_double(i2c_read_buffer3[0]);
			
		printk("i: %d Accel x: %.3f   Accel y: %.5f   Accel z: %.4f\n     DEGps x: %.3f   DEGps y: %.5f   DEGps z: %.4f\n\n",i,  accel_x,accel_y,accel_z, gyro_x,gyro_y,gyro_z);
		i++;
			
		k_msleep(3000);
	}
}
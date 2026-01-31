
LSM6DSV data reading via i2c
###########

Overview
********

A project that reads accelerometer data using i2c communication protocol. Gyroscope and axis accelerometer is used.

Sensor
********************

The LSM6DSV16X is an advanced inertial sensor from STMicroelectronics that integrates a 3-axis accelerometer and a 3-axis gyroscope in a single compact package. It is designed for applications that require accurate motion, orientation, and vibration measurements, such as wearables, IoT devices, consumer electronics, and embedded systems, while maintaining low power consumption.

A key feature of the LSM6DSV16X is its I2C communication interface, which enables simple and reliable integration with low-power microcontrollers. The I²C bus uses only two signal lines (SCL and SDA), reducing pin count and simplifying PCB design—an important advantage in space-constrained devices. Through this interface, the sensor provides access to a well-organized register map that allows configuration of measurement ranges, output data rates, digital filters, and power modes, as well as efficient reading of accelerometer and gyroscope data.

The sensor supports standard and fast I2C speeds, making it suitable for both periodic sampling and event-driven data acquisition. In addition, configurable interrupt pins can be used alongside the I²C interface to notify the host system of relevant motion events, further reducing overall system power consumption.

Overall, the combination of precise inertial sensing, embedded processing capabilities, and a flexible, widely supported I2C interface makes the LSM6DSV16X a reliable and efficient solution for modern motion-sensing applications.

To build for another board, change "qemu_x86" above to that board's name.

Sample Output
=============

.. code-block:: console

    Accelerometer data

Exit QEMU by pressing :kbd:`CTRL+A` :kbd:`x`.

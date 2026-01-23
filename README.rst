
LSM6DSV data reading via i2c
###########

Overview
********

A project that reads accelerometer data using i2c communication protocol. Gyroscope and axis accelerometer is used.

Building and Running
********************

This application can be built and executed on QEMU as follows:

.. zephyr-app-commands::
   :host-os: unix
   :board: qemu_x86
   :compact:

To build for another board, change "qemu_x86" above to that board's name.

Sample Output
=============

.. code-block:: console

    Hello World! x86

Exit QEMU by pressing :kbd:`CTRL+A` :kbd:`x`.

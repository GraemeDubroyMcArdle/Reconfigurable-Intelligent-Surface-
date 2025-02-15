# Reconfigurable-Intelligent-Surface-
This is a final capstone project divided into 2 catagories, Reflective Surface and Absorption Surface

The Reflective Panel takes advantage of the of constructive and destructive inteference in order to steer the beam laser.
Using an STM32 Array, a instruction is sent from the master controller to several secondary controllers using the I2C .wire communication protocol
The Slave boards then trigger Transistors to allow current from a 5V bus to place a forward bias current onto a pin diode, creating capacitance on the surface.
In turn, this Capacitance affects the reflection coefficient, allowing for beam steering

The absorption panel requires us to match the transmitted incident wave's impedance in order to achieve perfect absorption.
This means both the capacitance, and impedance must be seperately tuned to achieve the exact target. This means an I2C DAC (MCP4725) will be used to provide analog control voltage to the components.
In order to increase our I2C capabilities, several multiplexers (TCA9548A) will also be used in order to achieve control.


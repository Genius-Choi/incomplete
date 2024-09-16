JshPinFunction jshGetPinFunctionFromDevice(IOEventFlags device) {
 if (DEVICE_IS_USART(device))
   return JSH_USART1 + ((device - EV_SERIAL1)<<JSH_SHIFT_TYPE);
 if (DEVICE_IS_SPI(device))
   return JSH_SPI1 + ((device - EV_SPI1)<<JSH_SHIFT_TYPE);
 if (DEVICE_IS_I2C(device))
   return JSH_I2C1 + ((device - EV_I2C1)<<JSH_SHIFT_TYPE);
 return 0;
}

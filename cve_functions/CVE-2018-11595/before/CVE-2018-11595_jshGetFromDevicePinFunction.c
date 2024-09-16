IOEventFlags jshGetFromDevicePinFunction(JshPinFunction func) {
 if (JSH_PINFUNCTION_IS_USART(func))
   return EV_SERIAL1 + ((func - JSH_USART1) >> JSH_SHIFT_TYPE);
 if (JSH_PINFUNCTION_IS_SPI(func))
   return EV_SPI1 + ((func - JSH_SPI1) >> JSH_SHIFT_TYPE);
 if (JSH_PINFUNCTION_IS_I2C(func))
   return EV_I2C1 + ((func - JSH_I2C1) >> JSH_SHIFT_TYPE);
 return 0;
}

JshPinFunction NO_INLINE jshGetPinFunctionForPin(Pin pin, JshPinFunction functionType) {
  if (!jshIsPinValid(pin)) return 0;
  int i;
  for (i=0;i<JSH_PININFO_FUNCTIONS;i++) {
    if ((pinInfo[pin].functions[i]&JSH_MASK_TYPE) == functionType)
      return pinInfo[pin].functions[i];
  }
  return 0;
}

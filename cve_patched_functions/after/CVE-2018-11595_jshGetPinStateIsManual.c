bool jshGetPinStateIsManual(Pin pin) {
  return BITFIELD_GET(jshPinStateIsManual, pin);
}

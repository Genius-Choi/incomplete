JsVar *jshGetDeviceObjectFor(JshPinFunction deviceMin, JshPinFunction deviceMax, Pin pin) {
  JshPinFunction dev = jshGetDeviceFor(deviceMin, deviceMax, pin);
  if (dev==JSH_NOTHING) return 0;
  char devName[16];
  jshPinFunctionToString(dev, JSPFTS_DEVICE|JSPFTS_DEVICE_NUMBER|JSPFTS_JS_NAMES, devName, sizeof(devName));
  JsVar *devVar = jsvObjectGetChild(execInfo.root, devName, 0);
  if (devVar) return devVar;
  return jswFindBuiltInFunction(0, devName);
}

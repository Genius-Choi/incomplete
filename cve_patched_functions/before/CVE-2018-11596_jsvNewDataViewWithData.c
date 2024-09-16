JsVar *jsvNewDataViewWithData(JsVarInt length, unsigned char *data) {
  JsVar *buf = jswrap_arraybuffer_constructor(length);
  if (!buf) return 0;
  JsVar *view = jswrap_dataview_constructor(buf, 0, 0);
  if (!view) {
    jsvUnLock(buf);
    return 0;
  }
  if (data) {
    JsVar *arrayBufferData = jsvGetArrayBufferBackingString(buf);
    if (arrayBufferData)
      jsvSetString(arrayBufferData, (char *)data, (size_t)length);
    jsvUnLock(arrayBufferData);
  }
  jsvUnLock(buf);
  return view;
}

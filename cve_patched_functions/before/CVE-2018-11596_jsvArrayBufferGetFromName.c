JsVar *jsvArrayBufferGetFromName(JsVar *name) {
  assert(jsvIsArrayBufferName(name));
  size_t idx = (size_t)jsvGetInteger(name);
  JsVar *arrayBuffer = jsvLock(jsvGetFirstChild(name));
  JsVar *value = jsvArrayBufferGet(arrayBuffer, idx);
  jsvUnLock(arrayBuffer);
  return value;
}

JsVar *jspCallNamedFunction(JsVar *object, char* name, int argCount, JsVar **argPtr) {
  JsVar *child = jspGetNamedField(object, name, false);
  JsVar *r = 0;
  if (jsvIsFunction(child))
    r = jspeFunctionCall(child, 0, object, false, argCount, argPtr);
  jsvUnLock(child);
  return r;
}

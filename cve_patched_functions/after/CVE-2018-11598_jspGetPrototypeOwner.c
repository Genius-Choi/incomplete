JsVar *jspGetPrototypeOwner(JsVar *proto) {
  if (jsvIsObject(proto) || jsvIsArray(proto)) {
    return jsvSkipNameAndUnLock(jsvObjectGetChild(proto, JSPARSE_CONSTRUCTOR_VAR, 0));
  }
  return 0;
}

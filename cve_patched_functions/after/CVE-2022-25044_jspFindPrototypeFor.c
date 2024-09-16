JsVar *jspFindPrototypeFor(const char *className) {
  JsVar *obj = jsvObjectGetChild(execInfo.root, className, 0);
  if (!obj) return 0;
  JsVar *proto = jsvObjectGetChild(obj, JSPARSE_PROTOTYPE_VAR, 0);
  jsvUnLock(obj);
  return proto;
}

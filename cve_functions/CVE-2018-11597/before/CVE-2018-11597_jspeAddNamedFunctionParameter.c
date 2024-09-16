NO_INLINE JsVar *jspeAddNamedFunctionParameter(JsVar *funcVar, JsVar *name) {
  if (!funcVar) funcVar = jsvNewWithFlags(JSV_FUNCTION);
  char buf[JSLEX_MAX_TOKEN_LENGTH+1];
  buf[0] = '\xFF';
  jsvGetString(name, &buf[1], JSLEX_MAX_TOKEN_LENGTH);
  JsVar *param = jsvAddNamedChild(funcVar, 0, buf);
  jsvMakeFunctionParameter(param);
  jsvUnLock(param);
  return funcVar;
}

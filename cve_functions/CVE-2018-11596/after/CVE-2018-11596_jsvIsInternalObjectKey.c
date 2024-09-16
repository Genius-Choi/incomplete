bool jsvIsInternalObjectKey(JsVar *v) {
  return (jsvIsString(v) && (
      v->varData.str[0]==JS_HIDDEN_CHAR ||
      jsvIsStringEqual(v, JSPARSE_INHERITS_VAR) ||
      jsvIsStringEqual(v, JSPARSE_CONSTRUCTOR_VAR)
  ));
}

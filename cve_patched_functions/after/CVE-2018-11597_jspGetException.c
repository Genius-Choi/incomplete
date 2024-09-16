JsVar *jspGetException() {
  JsVar *exceptionName = jsvFindChildFromString(execInfo.hiddenRoot, JSPARSE_EXCEPTION_VAR, false);
  if (exceptionName) {
    JsVar *exception = jsvSkipName(exceptionName);
    jsvRemoveChild(execInfo.hiddenRoot, exceptionName);
    jsvUnLock(exceptionName);

    JsVar *stack = jspGetStackTrace();
    if (stack && jsvHasChildren(exception)) {
      jsvObjectSetChild(exception, "stack", stack);
    }
    jsvUnLock(stack);

    return exception;
  }
  return 0;
}

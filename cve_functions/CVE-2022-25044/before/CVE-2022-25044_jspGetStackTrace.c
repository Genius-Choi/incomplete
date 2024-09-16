JsVar *jspGetStackTrace() {
  JsVar *stackTraceName = jsvFindChildFromString(execInfo.hiddenRoot, JSPARSE_STACKTRACE_VAR, false);
  if (stackTraceName) {
    JsVar *stackTrace = jsvSkipName(stackTraceName);
    jsvRemoveChild(execInfo.hiddenRoot, stackTraceName);
    jsvUnLock(stackTraceName);
    return stackTrace;
  }
  return 0;
}

void jspSetError(bool lineReported) {
  execInfo.execute = (execInfo.execute & (JsExecFlags)~EXEC_YES) | EXEC_ERROR;
  if (lineReported)
    execInfo.execute |= EXEC_ERROR_LINE_REPORTED;
}

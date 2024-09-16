ALWAYS_INLINE void jspDebuggerLoopIfCtrlC() {
#ifdef USE_DEBUGGER
  if (execInfo.execute & EXEC_CTRL_C_WAIT && JSP_SHOULD_EXECUTE)
    jsiDebuggerLoop();
#endif
}

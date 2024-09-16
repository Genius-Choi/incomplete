void jspAppendStackTrace(JsVar *stackTrace) {
  JsvStringIterator it;
  jsvStringIteratorNew(&it, stackTrace, 0);
  jsvStringIteratorGotoEnd(&it);
  jslPrintPosition((vcbprintf_callback)jsvStringIteratorPrintfCallback, &it, lex->tokenLastStart);
  jslPrintTokenLineMarker((vcbprintf_callback)jsvStringIteratorPrintfCallback, &it, lex->tokenLastStart, 0);
  jsvStringIteratorFree(&it);
}

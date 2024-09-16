JsVar *jsvGetIndexOfFull(JsVar *arr, JsVar *value, bool matchExact, bool matchIntegerIndices, int startIdx) {
  JsVarRef indexref;
  assert(jsvIsArray(arr) || jsvIsObject(arr));
  indexref = jsvGetFirstChild(arr);
  while (indexref) {
    JsVar *childIndex = jsvLock(indexref);
    if (!matchIntegerIndices ||
        (jsvIsInt(childIndex) && jsvGetInteger(childIndex)>=startIdx)) {
      assert(jsvIsName(childIndex));
      JsVar *childValue = jsvSkipName(childIndex);
      if (childValue==value ||
          (!matchExact && jsvMathsOpTypeEqual(childValue, value))) {
        jsvUnLock(childValue);
        return childIndex;
      }
      jsvUnLock(childValue);
    }
    indexref = jsvGetNextSibling(childIndex);
    jsvUnLock(childIndex);
  }
  return 0; // undefined
}

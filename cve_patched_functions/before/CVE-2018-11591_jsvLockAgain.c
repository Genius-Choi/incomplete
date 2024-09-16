ALWAYS_INLINE JsVar *jsvLockAgain(JsVar *var) {
  assert(var);
  assert(jsvGetLocks(var) < JSV_LOCK_MAX);
  var->flags += JSV_LOCK_ONE;
  return var;
}

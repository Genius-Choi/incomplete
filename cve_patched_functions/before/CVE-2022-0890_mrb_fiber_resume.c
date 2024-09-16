mrb_fiber_resume(mrb_state *mrb, mrb_value fib, mrb_int len, const mrb_value *a)
{
  return fiber_switch(mrb, fib, len, a, TRUE, TRUE);
}

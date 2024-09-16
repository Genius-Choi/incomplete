fiber_eq(mrb_state *mrb, mrb_value self)
{
  mrb_value other = mrb_get_arg1(mrb);

  if (!mrb_fiber_p(other)) {
    return mrb_false_value();
  }
  return mrb_bool_value(fiber_ptr(self) == fiber_ptr(other));
}

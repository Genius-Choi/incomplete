mrb_obj_ivar_defined(mrb_state *mrb, mrb_value self)
{
  mrb_sym sym;

  mrb_get_args(mrb, "n", &sym);
  mrb_iv_check(mrb, sym);
  return mrb_bool_value(mrb_iv_defined(mrb, self, sym));
}

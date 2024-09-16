mrb_obj_basic_to_s_p(mrb_state *mrb, mrb_value obj)
{
  return mrb_func_basic_p(mrb, obj, mrb_intern_lit(mrb, "to_s"), mrb_any_to_s);
}

mrb_obj_class(mrb_state *mrb, mrb_value obj)
{
  return mrb_class_real(mrb_class(mrb, obj));
}

mrb_obj_methods(mrb_state *mrb, mrb_bool recur, mrb_value obj, mrb_method_flag_t flag)
{
  return mrb_class_instance_method_list(mrb, recur, mrb_class(mrb, obj), 0);
}

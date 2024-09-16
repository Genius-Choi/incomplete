undef_method(mrb_state *mrb, struct RClass *c, mrb_sym a)
{
  if (!mrb_obj_respond_to(mrb, c, a)) {
    mrb_name_error(mrb, a, "undefined method '%S' for class '%S'", mrb_sym2str(mrb, a), mrb_obj_value(c));
  }
  else {
    mrb_method_t m;

    MRB_METHOD_FROM_PROC(m, NULL);
    mrb_define_method_raw(mrb, c, a, m);
  }
}

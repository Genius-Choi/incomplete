check_type(mrb_state *mrb, mrb_value val, enum mrb_vtype t, const char *c, const char *m)
{
  mrb_value tmp;

  tmp = mrb_check_convert_type(mrb, val, t, c, m);
  if (mrb_nil_p(tmp)) {
    mrb_raisef(mrb, E_TYPE_ERROR, "expected %S", mrb_str_new_cstr(mrb, c));
  }
  return tmp;
}

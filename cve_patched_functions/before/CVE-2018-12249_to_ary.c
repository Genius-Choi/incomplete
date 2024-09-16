to_ary(mrb_state *mrb, mrb_value val)
{
  return check_type(mrb, val, MRB_TT_ARRAY, "Array", "to_ary");
}

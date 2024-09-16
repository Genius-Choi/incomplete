mrb_vm_define_module(mrb_state *mrb, mrb_value outer, mrb_sym id)
{
  check_if_class_or_module(mrb, outer);
  if (mrb_const_defined_at(mrb, outer, id)) {
    mrb_value old = mrb_const_get(mrb, outer, id);

    if (mrb_type(old) != MRB_TT_MODULE) {
      mrb_raisef(mrb, E_TYPE_ERROR, "%S is not a module", mrb_inspect(mrb, old));
    }
    return mrb_class_ptr(old);
  }
  return define_module(mrb, id, mrb_class_ptr(outer));
}

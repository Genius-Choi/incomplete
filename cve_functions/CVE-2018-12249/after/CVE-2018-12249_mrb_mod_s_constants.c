mrb_mod_s_constants(mrb_state *mrb, mrb_value mod)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Module.constants not implemented");
  return mrb_nil_value();       /* not reached */
}

boot_defclass(mrb_state *mrb, struct RClass *super)
{
  struct RClass *c;

  c = (struct RClass*)mrb_obj_alloc(mrb, MRB_TT_CLASS, mrb->class_class);
  if (super) {
    c->super = super;
    mrb_field_write_barrier(mrb, (struct RBasic*)c, (struct RBasic*)super);
  }
  else {
    c->super = mrb->object_class;
  }
  c->mt = kh_init(mt, mrb);
  return c;
}

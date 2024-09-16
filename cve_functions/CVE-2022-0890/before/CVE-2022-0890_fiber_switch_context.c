fiber_switch_context(mrb_state *mrb, struct mrb_context *c)
{
  if (mrb->c->fib) {
    mrb_write_barrier(mrb, (struct RBasic*)mrb->c->fib);
  }
  c->status = MRB_FIBER_RUNNING;
  mrb->c = c;
}

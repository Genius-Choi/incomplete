final_marking_phase(mrb_state *mrb, mrb_gc *gc)
{
  mark_context_stack(mrb, mrb->root_c);
  gc_mark_gray_list(mrb, gc);
  mrb_assert(gc->gray_list == NULL);
  gc->gray_list = gc->atomic_gray_list;
  gc->atomic_gray_list = NULL;
  gc_mark_gray_list(mrb, gc);
  mrb_assert(gc->gray_list == NULL);
}

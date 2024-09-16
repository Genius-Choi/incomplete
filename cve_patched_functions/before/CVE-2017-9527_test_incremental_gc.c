test_incremental_gc(void)
{
  mrb_state *mrb = mrb_open();
  size_t max = ~0, live = 0, total = 0, freed = 0;
  RVALUE *free;
  mrb_heap_page *page;
  mrb_gc *gc = &mrb->gc;

  puts("test_incremental_gc");
  change_gen_gc_mode(mrb, gc, FALSE);

  puts("  in mrb_full_gc");
  mrb_full_gc(mrb);

  mrb_assert(gc->state == MRB_GC_STATE_ROOT);
  puts("  in MRB_GC_STATE_ROOT");
  incremental_gc(mrb, gc, max);
  mrb_assert(gc->state == MRB_GC_STATE_MARK);
  puts("  in MRB_GC_STATE_MARK");
  incremental_gc_until(mrb, gc, MRB_GC_STATE_SWEEP);
  mrb_assert(gc->state == MRB_GC_STATE_SWEEP);

  puts("  in MRB_GC_STATE_SWEEP");
  page = gc->heaps;
  while (page) {
    RVALUE *p = objects(page);
    RVALUE *e = p + MRB_HEAP_PAGE_SIZE;
    while (p<e) {
      if (is_black(&p->as.basic)) {
        live++;
      }
      if (is_gray(&p->as.basic) && !is_dead(gc, &p->as.basic)) {
        printf("%p\n", &p->as.basic);
      }
      p++;
    }
    page = page->next;
    total += MRB_HEAP_PAGE_SIZE;
  }

  mrb_assert(gc->gray_list == NULL);

  incremental_gc(mrb, gc, max);
  mrb_assert(gc->state == MRB_GC_STATE_SWEEP);

  incremental_gc(mrb, gc, max);
  mrb_assert(gc->state == MRB_GC_STATE_ROOT);

  free = (RVALUE*)gc->heaps->freelist;
  while (free) {
   freed++;
   free = (RVALUE*)free->as.free.next;
  }

  mrb_assert(gc->live == live);
  mrb_assert(gc->live == total-freed);

  puts("test_incremental_gc(gen)");
  incremental_gc_until(mrb, gc, MRB_GC_STATE_SWEEP);
  change_gen_gc_mode(mrb, gc, TRUE);

  mrb_assert(gc->full == FALSE);
  mrb_assert(gc->state == MRB_GC_STATE_ROOT);

  puts("  in minor");
  mrb_assert(is_minor_gc(gc));
  mrb_assert(gc->majorgc_old_threshold > 0);
  gc->majorgc_old_threshold = 0;
  mrb_incremental_gc(mrb);
  mrb_assert(gc->full == TRUE);
  mrb_assert(gc->state == MRB_GC_STATE_ROOT);

  puts("  in major");
  mrb_assert(is_major_gc(gc));
  do {
    mrb_incremental_gc(mrb);
  } while (gc->state != MRB_GC_STATE_ROOT);
  mrb_assert(gc->full == FALSE);

  mrb_close(mrb);
}

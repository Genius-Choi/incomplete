gc_each_objects(mrb_state *mrb, mrb_gc *gc, mrb_each_object_callback *callback, void *data)
{
  mrb_heap_page* page = gc->heaps;

  while (page != NULL) {
    RVALUE *p, *pend;

    p = objects(page);
    pend = p + MRB_HEAP_PAGE_SIZE;
    for (;p < pend; p++) {
      (*callback)(mrb, &p->as.basic, data);
    }

    page = page->next;
  }
}

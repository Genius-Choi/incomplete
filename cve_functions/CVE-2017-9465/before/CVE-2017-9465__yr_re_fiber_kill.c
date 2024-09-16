RE_FIBER* _yr_re_fiber_kill(
    RE_FIBER_LIST* fiber_list,
    RE_FIBER_POOL* fiber_pool,
    RE_FIBER* fiber)
{
  RE_FIBER* next_fiber = fiber->next;

  if (fiber->prev != NULL)
    fiber->prev->next = next_fiber;

  if (next_fiber != NULL)
    next_fiber->prev = fiber->prev;

  if (fiber_pool->fibers.tail != NULL)
    fiber_pool->fibers.tail->next = fiber;

  if (fiber_list->tail == fiber)
    fiber_list->tail = fiber->prev;

  if (fiber_list->head == fiber)
    fiber_list->head = next_fiber;

  fiber->next = NULL;
  fiber->prev = fiber_pool->fibers.tail;
  fiber_pool->fibers.tail = fiber;

  if (fiber_pool->fibers.head == NULL)
    fiber_pool->fibers.head = fiber;

  return next_fiber;
}

YR_ARENA_PAGE* _yr_arena_new_page(
    size_t size)
{
  YR_ARENA_PAGE* new_page;

  new_page = (YR_ARENA_PAGE*) yr_malloc(sizeof(YR_ARENA_PAGE));

  if (new_page == NULL)
    return NULL;

  new_page->address = (uint8_t*) yr_malloc(size);

  if (new_page->address == NULL)
  {
    yr_free(new_page);
    return NULL;
  }

  new_page->size = size;
  new_page->used = 0;
  new_page->next = NULL;
  new_page->prev = NULL;
  new_page->reloc_list_head = NULL;
  new_page->reloc_list_tail = NULL;

  return new_page;
}

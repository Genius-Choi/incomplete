void* yr_arena_next_address(
  YR_ARENA* arena,
  void* address,
  size_t offset)
{
  YR_ARENA_PAGE* page;

  page = _yr_arena_page_for_address(arena, address);

  assert(page != NULL);

  if ((uint8_t*) address + offset >= page->address &&
      (uint8_t*) address + offset < page->address + page->used)
  {
    return (uint8_t*) address + offset;
  }

  if (offset > 0)
  {
    offset -= page->address + page->used - (uint8_t*) address;
    page = page->next;

    while (page != NULL)
    {
      if (offset < page->used)
        return page->address + offset;

      offset -= page->used;
      page = page->next;
    }
  }
  else
  {
    offset += page->used;
    page = page->prev;

    while (page != NULL)
    {
      if (offset < page->used)
        return page->address + page->used + offset;

      offset += page->used;
      page = page->prev;
    }
  }

  return NULL;
}

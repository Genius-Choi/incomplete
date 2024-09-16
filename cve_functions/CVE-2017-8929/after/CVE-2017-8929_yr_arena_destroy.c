void yr_arena_destroy(
    YR_ARENA* arena)
{
  YR_RELOC* reloc;
  YR_RELOC* next_reloc;
  YR_ARENA_PAGE* page;
  YR_ARENA_PAGE* next_page;

  if (arena == NULL)
    return;

  page = arena->page_list_head;

  while(page != NULL)
  {
    next_page = page->next;
    reloc = page->reloc_list_head;

    while (reloc != NULL)
    {
      next_reloc = reloc->next;
      yr_free(reloc);
      reloc = next_reloc;
    }

    yr_free(page->address);
    yr_free(page);

    page = next_page;
  }

  yr_free(arena);
}

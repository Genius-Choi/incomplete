void* yr_arena_base_address(
  YR_ARENA* arena)
{
  if (arena->page_list_head->used == 0)
    return NULL;

  return arena->page_list_head->address;
}

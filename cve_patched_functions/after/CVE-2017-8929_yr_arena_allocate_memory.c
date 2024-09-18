int yr_arena_allocate_memory(
    YR_ARENA* arena,
    size_t size,
    void** allocated_memory)
{
  FAIL_ON_ERROR(yr_arena_reserve_memory(arena, size));

  *allocated_memory = arena->current_page->address + \
                      arena->current_page->used;

  arena->current_page->used += size;

  return ERROR_SUCCESS;
}

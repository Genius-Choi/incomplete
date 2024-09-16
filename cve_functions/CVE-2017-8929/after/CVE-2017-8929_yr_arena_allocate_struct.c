int yr_arena_allocate_struct(
    YR_ARENA* arena,
    size_t size,
    void** allocated_memory,
    ...)
{
  int result;

  va_list offsets;
  va_start(offsets, allocated_memory);

  result = yr_arena_allocate_memory(arena, size, allocated_memory);

  if (result == ERROR_SUCCESS)
    result = _yr_arena_make_relocatable(arena, *allocated_memory, offsets);

  va_end(offsets);

  if (result == ERROR_SUCCESS)
    memset(*allocated_memory, 0, size);

  return result;
}

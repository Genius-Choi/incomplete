int yr_arena_make_relocatable(
    YR_ARENA* arena,
    void* base,
    ...)
{
  int result;

  va_list offsets;
  va_start(offsets, base);

  result = _yr_arena_make_relocatable(arena, base, offsets);

  va_end(offsets);

  return result;
}

int yr_arena_append(
    YR_ARENA* target_arena,
    YR_ARENA* source_arena)
{
  uint8_t padding_data[15];
  size_t padding_size = 16 - target_arena->current_page->used % 16;

  if (padding_size < 16)
  {
    memset(&padding_data, 0xCC, padding_size);

    FAIL_ON_ERROR(yr_arena_write_data(
        target_arena,
        padding_data,
        padding_size,
        NULL));
  }

  target_arena->current_page->next = source_arena->page_list_head;
  source_arena->page_list_head->prev = target_arena->current_page;
  target_arena->current_page = source_arena->current_page;

  yr_free(source_arena);

  return ERROR_SUCCESS;
}

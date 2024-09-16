init_cell_pool(void)
{
  tor_assert(!cell_pool);
  cell_pool = mp_pool_new(sizeof(packed_cell_t), 128*1024);
}

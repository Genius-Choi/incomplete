entry_guard_find_node(const entry_guard_t *guard)
{
  tor_assert(guard);
  return node_get_by_id(guard->identity);
}

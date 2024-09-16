entry_guard_free(entry_guard_t *e)
{
  if (!e)
    return;
  entry_guard_handles_clear(e);
  tor_free(e->sampled_by_version);
  tor_free(e->extra_state_fields);
  tor_free(e->selection_name);
  tor_free(e->bridge_addr);
  tor_free(e);
}

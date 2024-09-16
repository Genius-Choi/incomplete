get_guard_selection_by_name(const char *name,
                            guard_selection_type_t type,
                            int create_if_absent)
{
  if (!guard_contexts) {
    guard_contexts = smartlist_new();
  }
  SMARTLIST_FOREACH_BEGIN(guard_contexts, guard_selection_t *, gs) {
    if (!strcmp(gs->name, name))
      return gs;
  } SMARTLIST_FOREACH_END(gs);

  if (! create_if_absent)
    return NULL;

  log_debug(LD_GUARD, "Creating a guard selection called %s", name);
  guard_selection_t *new_selection = guard_selection_new(name, type);
  smartlist_add(guard_contexts, new_selection);

  return new_selection;
}

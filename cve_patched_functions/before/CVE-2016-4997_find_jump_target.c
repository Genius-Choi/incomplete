static bool find_jump_target(const struct xt_table_info *t,
			     const struct ip6t_entry *target)
{
	struct ip6t_entry *iter;

	xt_entry_foreach(iter, t->entries, t->size) {
		 if (iter == target)
			return true;
	}
	return false;
}

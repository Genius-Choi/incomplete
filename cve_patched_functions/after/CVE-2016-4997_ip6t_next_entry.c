ip6t_next_entry(const struct ip6t_entry *entry)
{
	return (void *)entry + entry->next_offset;
}

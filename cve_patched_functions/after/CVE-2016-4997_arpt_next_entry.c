struct arpt_entry *arpt_next_entry(const struct arpt_entry *entry)
{
	return (void *)entry + entry->next_offset;
}

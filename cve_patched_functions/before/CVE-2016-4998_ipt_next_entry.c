struct ipt_entry *ipt_next_entry(const struct ipt_entry *entry)
{
	return (void *)entry + entry->next_offset;
}

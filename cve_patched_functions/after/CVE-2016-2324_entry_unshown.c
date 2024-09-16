static int entry_unshown(struct object_array_entry *entry, void *cb_data_unused)
{
	return !(entry->item->flags & SHOWN);
}

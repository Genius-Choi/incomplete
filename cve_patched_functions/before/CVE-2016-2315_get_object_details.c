static void get_object_details(void)
{
	uint32_t i;
	struct object_entry **sorted_by_offset;

	sorted_by_offset = xcalloc(to_pack.nr_objects, sizeof(struct object_entry *));
	for (i = 0; i < to_pack.nr_objects; i++)
		sorted_by_offset[i] = to_pack.objects + i;
	qsort(sorted_by_offset, to_pack.nr_objects, sizeof(*sorted_by_offset), pack_offset_sort);

	for (i = 0; i < to_pack.nr_objects; i++) {
		struct object_entry *entry = sorted_by_offset[i];
		check_object(entry);
		if (big_file_threshold < entry->size)
			entry->no_try_delta = 1;
	}

	free(sorted_by_offset);
}

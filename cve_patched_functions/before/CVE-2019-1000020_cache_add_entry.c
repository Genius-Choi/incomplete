cache_add_entry(struct iso9660 *iso9660, struct file_info *file)
{
	file->next = NULL;
	*iso9660->cache_files.last = file;
	iso9660->cache_files.last = &(file->next);
}

FILE *write_mount_file(struct lxc_list *mount)
{
	FILE *file;
	struct lxc_list *iterator;
	char *mount_entry;

	file = tmpfile();
	if (!file) {
		ERROR("tmpfile error: %m");
		return NULL;
	}

	lxc_list_for_each(iterator, mount) {
		mount_entry = iterator->elem;
		fprintf(file, "%s\n", mount_entry);
	}

	rewind(file);
	return file;
}

static void add_preferred_base(unsigned char *sha1)
{
	struct pbase_tree *it;
	void *data;
	unsigned long size;
	unsigned char tree_sha1[20];

	if (window <= num_preferred_base++)
		return;

	data = read_object_with_reference(sha1, tree_type, &size, tree_sha1);
	if (!data)
		return;

	for (it = pbase_tree; it; it = it->next) {
		if (!hashcmp(it->pcache.sha1, tree_sha1)) {
			free(data);
			return;
		}
	}

	it = xcalloc(1, sizeof(*it));
	it->next = pbase_tree;
	pbase_tree = it;

	hashcpy(it->pcache.sha1, tree_sha1);
	it->pcache.tree_data = data;
	it->pcache.tree_size = size;
}

static unsigned long free_unpacked(struct unpacked *n)
{
	unsigned long freed_mem = sizeof_delta_index(n->index);
	free_delta_index(n->index);
	n->index = NULL;
	if (n->data) {
		freed_mem += n->entry->size;
		free(n->data);
		n->data = NULL;
	}
	n->entry = NULL;
	n->depth = 0;
	return freed_mem;
}

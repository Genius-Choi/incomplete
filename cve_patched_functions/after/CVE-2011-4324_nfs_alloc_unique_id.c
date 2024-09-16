static void nfs_alloc_unique_id(struct rb_root *root, struct nfs_unique_id *new,
		__u64 minval, int maxbits)
{
	struct rb_node **p, *parent;
	struct nfs_unique_id *pos;
	__u64 mask = ~0ULL;

	if (maxbits < 64)
		mask = (1ULL << maxbits) - 1ULL;

	/* Ensure distribution is more or less flat */
	get_random_bytes(&new->id, sizeof(new->id));
	new->id &= mask;
	if (new->id < minval)
		new->id += minval;
retry:
	p = &root->rb_node;
	parent = NULL;

	while (*p != NULL) {
		parent = *p;
		pos = rb_entry(parent, struct nfs_unique_id, rb_node);

		if (new->id < pos->id)
			p = &(*p)->rb_left;
		else if (new->id > pos->id)
			p = &(*p)->rb_right;
		else
			goto id_exists;
	}
	rb_link_node(&new->rb_node, parent, p);
	rb_insert_color(&new->rb_node, root);
	return;
id_exists:
	for (;;) {
		new->id++;
		if (new->id < minval || (new->id & mask) != new->id) {
			new->id = minval;
			break;
		}
		parent = rb_next(parent);
		if (parent == NULL)
			break;
		pos = rb_entry(parent, struct nfs_unique_id, rb_node);
		if (new->id < pos->id)
			break;
	}
	goto retry;
}

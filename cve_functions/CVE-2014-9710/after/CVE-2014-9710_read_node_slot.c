static noinline struct extent_buffer *read_node_slot(struct btrfs_root *root,
				   struct extent_buffer *parent, int slot)
{
	int level = btrfs_header_level(parent);
	struct extent_buffer *eb;

	if (slot < 0)
		return NULL;
	if (slot >= btrfs_header_nritems(parent))
		return NULL;

	BUG_ON(level == 0);

	eb = read_tree_block(root, btrfs_node_blockptr(parent, slot),
			     btrfs_node_ptr_generation(parent, slot));
	if (eb && !extent_buffer_uptodate(eb)) {
		free_extent_buffer(eb);
		eb = NULL;
	}

	return eb;
}

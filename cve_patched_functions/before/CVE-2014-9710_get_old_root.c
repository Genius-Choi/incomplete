get_old_root(struct btrfs_root *root, u64 time_seq)
{
	struct tree_mod_elem *tm;
	struct extent_buffer *eb = NULL;
	struct extent_buffer *eb_root;
	struct extent_buffer *old;
	struct tree_mod_root *old_root = NULL;
	u64 old_generation = 0;
	u64 logical;

	eb_root = btrfs_read_lock_root_node(root);
	tm = __tree_mod_log_oldest_root(root->fs_info, eb_root, time_seq);
	if (!tm)
		return eb_root;

	if (tm->op == MOD_LOG_ROOT_REPLACE) {
		old_root = &tm->old_root;
		old_generation = tm->generation;
		logical = old_root->logical;
	} else {
		logical = eb_root->start;
	}

	tm = tree_mod_log_search(root->fs_info, logical, time_seq);
	if (old_root && tm && tm->op != MOD_LOG_KEY_REMOVE_WHILE_FREEING) {
		btrfs_tree_read_unlock(eb_root);
		free_extent_buffer(eb_root);
		old = read_tree_block(root, logical, 0);
		if (WARN_ON(!old || !extent_buffer_uptodate(old))) {
			free_extent_buffer(old);
			btrfs_warn(root->fs_info,
				"failed to read tree block %llu from get_old_root", logical);
		} else {
			eb = btrfs_clone_extent_buffer(old);
			free_extent_buffer(old);
		}
	} else if (old_root) {
		btrfs_tree_read_unlock(eb_root);
		free_extent_buffer(eb_root);
		eb = alloc_dummy_extent_buffer(logical, root->nodesize);
	} else {
		btrfs_set_lock_blocking_rw(eb_root, BTRFS_READ_LOCK);
		eb = btrfs_clone_extent_buffer(eb_root);
		btrfs_tree_read_unlock_blocking(eb_root);
		free_extent_buffer(eb_root);
	}

	if (!eb)
		return NULL;
	extent_buffer_get(eb);
	btrfs_tree_read_lock(eb);
	if (old_root) {
		btrfs_set_header_bytenr(eb, eb->start);
		btrfs_set_header_backref_rev(eb, BTRFS_MIXED_BACKREF_REV);
		btrfs_set_header_owner(eb, btrfs_header_owner(eb_root));
		btrfs_set_header_level(eb, old_root->level);
		btrfs_set_header_generation(eb, old_generation);
	}
	if (tm)
		__tree_mod_log_rewind(root->fs_info, eb, time_seq, tm);
	else
		WARN_ON(btrfs_header_level(eb) != 0);
	WARN_ON(btrfs_header_nritems(eb) > BTRFS_NODEPTRS_PER_BLOCK(root));

	return eb;
}

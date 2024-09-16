tree_mod_log_insert_root(struct btrfs_fs_info *fs_info,
			 struct extent_buffer *old_root,
			 struct extent_buffer *new_root, gfp_t flags,
			 int log_removal)
{
	struct tree_mod_elem *tm = NULL;
	struct tree_mod_elem **tm_list = NULL;
	int nritems = 0;
	int ret = 0;
	int i;

	if (!tree_mod_need_log(fs_info, NULL))
		return 0;

	if (log_removal && btrfs_header_level(old_root) > 0) {
		nritems = btrfs_header_nritems(old_root);
		tm_list = kzalloc(nritems * sizeof(struct tree_mod_elem *),
				  flags);
		if (!tm_list) {
			ret = -ENOMEM;
			goto free_tms;
		}
		for (i = 0; i < nritems; i++) {
			tm_list[i] = alloc_tree_mod_elem(old_root, i,
			    MOD_LOG_KEY_REMOVE_WHILE_FREEING, flags);
			if (!tm_list[i]) {
				ret = -ENOMEM;
				goto free_tms;
			}
		}
	}

	tm = kzalloc(sizeof(*tm), flags);
	if (!tm) {
		ret = -ENOMEM;
		goto free_tms;
	}

	tm->index = new_root->start >> PAGE_CACHE_SHIFT;
	tm->old_root.logical = old_root->start;
	tm->old_root.level = btrfs_header_level(old_root);
	tm->generation = btrfs_header_generation(old_root);
	tm->op = MOD_LOG_ROOT_REPLACE;

	if (tree_mod_dont_log(fs_info, NULL))
		goto free_tms;

	if (tm_list)
		ret = __tree_mod_log_free_eb(fs_info, tm_list, nritems);
	if (!ret)
		ret = __tree_mod_log_insert(fs_info, tm);

	tree_mod_log_write_unlock(fs_info);
	if (ret)
		goto free_tms;
	kfree(tm_list);

	return ret;

free_tms:
	if (tm_list) {
		for (i = 0; i < nritems; i++)
			kfree(tm_list[i]);
		kfree(tm_list);
	}
	kfree(tm);

	return ret;
}

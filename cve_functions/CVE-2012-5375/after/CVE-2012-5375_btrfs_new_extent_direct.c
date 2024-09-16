static struct extent_map *btrfs_new_extent_direct(struct inode *inode,
						  u64 start, u64 len)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_trans_handle *trans;
	struct extent_map *em;
	struct btrfs_key ins;
	u64 alloc_hint;
	int ret;

	trans = btrfs_join_transaction(root);
	if (IS_ERR(trans))
		return ERR_CAST(trans);

	trans->block_rsv = &root->fs_info->delalloc_block_rsv;

	alloc_hint = get_extent_allocation_hint(inode, start, len);
	ret = btrfs_reserve_extent(trans, root, len, root->sectorsize, 0,
				   alloc_hint, &ins, 1);
	if (ret) {
		em = ERR_PTR(ret);
		goto out;
	}

	em = create_pinned_em(inode, start, ins.offset, start, ins.objectid,
			      ins.offset, ins.offset, 0);
	if (IS_ERR(em))
		goto out;

	ret = btrfs_add_ordered_extent_dio(inode, start, ins.objectid,
					   ins.offset, ins.offset, 0);
	if (ret) {
		btrfs_free_reserved_extent(root, ins.objectid, ins.offset);
		em = ERR_PTR(ret);
	}
out:
	btrfs_end_transaction(trans, root);
	return em;
}

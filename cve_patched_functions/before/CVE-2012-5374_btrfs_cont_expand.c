int btrfs_cont_expand(struct inode *inode, loff_t oldsize, loff_t size)
{
	struct btrfs_trans_handle *trans;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	struct extent_map *em = NULL;
	struct extent_state *cached_state = NULL;
	struct extent_map_tree *em_tree = &BTRFS_I(inode)->extent_tree;
	u64 mask = root->sectorsize - 1;
	u64 hole_start = (oldsize + mask) & ~mask;
	u64 block_end = (size + mask) & ~mask;
	u64 last_byte;
	u64 cur_offset;
	u64 hole_size;
	int err = 0;

	if (size <= hole_start)
		return 0;

	while (1) {
		struct btrfs_ordered_extent *ordered;
		btrfs_wait_ordered_range(inode, hole_start,
					 block_end - hole_start);
		lock_extent_bits(io_tree, hole_start, block_end - 1, 0,
				 &cached_state);
		ordered = btrfs_lookup_ordered_extent(inode, hole_start);
		if (!ordered)
			break;
		unlock_extent_cached(io_tree, hole_start, block_end - 1,
				     &cached_state, GFP_NOFS);
		btrfs_put_ordered_extent(ordered);
	}

	cur_offset = hole_start;
	while (1) {
		em = btrfs_get_extent(inode, NULL, 0, cur_offset,
				block_end - cur_offset, 0);
		if (IS_ERR(em)) {
			err = PTR_ERR(em);
			break;
		}
		last_byte = min(extent_map_end(em), block_end);
		last_byte = (last_byte + mask) & ~mask;
		if (!test_bit(EXTENT_FLAG_PREALLOC, &em->flags)) {
			struct extent_map *hole_em;
			hole_size = last_byte - cur_offset;

			trans = btrfs_start_transaction(root, 3);
			if (IS_ERR(trans)) {
				err = PTR_ERR(trans);
				break;
			}

			err = btrfs_drop_extents(trans, root, inode,
						 cur_offset,
						 cur_offset + hole_size, 1);
			if (err) {
				btrfs_abort_transaction(trans, root, err);
				btrfs_end_transaction(trans, root);
				break;
			}

			err = btrfs_insert_file_extent(trans, root,
					btrfs_ino(inode), cur_offset, 0,
					0, hole_size, 0, hole_size,
					0, 0, 0);
			if (err) {
				btrfs_abort_transaction(trans, root, err);
				btrfs_end_transaction(trans, root);
				break;
			}

			btrfs_drop_extent_cache(inode, cur_offset,
						cur_offset + hole_size - 1, 0);
			hole_em = alloc_extent_map();
			if (!hole_em) {
				set_bit(BTRFS_INODE_NEEDS_FULL_SYNC,
					&BTRFS_I(inode)->runtime_flags);
				goto next;
			}
			hole_em->start = cur_offset;
			hole_em->len = hole_size;
			hole_em->orig_start = cur_offset;

			hole_em->block_start = EXTENT_MAP_HOLE;
			hole_em->block_len = 0;
			hole_em->orig_block_len = 0;
			hole_em->bdev = root->fs_info->fs_devices->latest_bdev;
			hole_em->compress_type = BTRFS_COMPRESS_NONE;
			hole_em->generation = trans->transid;

			while (1) {
				write_lock(&em_tree->lock);
				err = add_extent_mapping(em_tree, hole_em);
				if (!err)
					list_move(&hole_em->list,
						  &em_tree->modified_extents);
				write_unlock(&em_tree->lock);
				if (err != -EEXIST)
					break;
				btrfs_drop_extent_cache(inode, cur_offset,
							cur_offset +
							hole_size - 1, 0);
			}
			free_extent_map(hole_em);
next:
			btrfs_update_inode(trans, root, inode);
			btrfs_end_transaction(trans, root);
		}
		free_extent_map(em);
		em = NULL;
		cur_offset = last_byte;
		if (cur_offset >= block_end)
			break;
	}

	free_extent_map(em);
	unlock_extent_cached(io_tree, hole_start, block_end - 1, &cached_state,
			     GFP_NOFS);
	return err;
}

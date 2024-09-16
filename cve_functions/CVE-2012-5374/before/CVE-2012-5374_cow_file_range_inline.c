static noinline int cow_file_range_inline(struct btrfs_trans_handle *trans,
				 struct btrfs_root *root,
				 struct inode *inode, u64 start, u64 end,
				 size_t compressed_size, int compress_type,
				 struct page **compressed_pages)
{
	u64 isize = i_size_read(inode);
	u64 actual_end = min(end + 1, isize);
	u64 inline_len = actual_end - start;
	u64 aligned_end = (end + root->sectorsize - 1) &
			~((u64)root->sectorsize - 1);
	u64 data_len = inline_len;
	int ret;

	if (compressed_size)
		data_len = compressed_size;

	if (start > 0 ||
	    actual_end >= PAGE_CACHE_SIZE ||
	    data_len >= BTRFS_MAX_INLINE_DATA_SIZE(root) ||
	    (!compressed_size &&
	    (actual_end & (root->sectorsize - 1)) == 0) ||
	    end + 1 < isize ||
	    data_len > root->fs_info->max_inline) {
		return 1;
	}

	ret = btrfs_drop_extents(trans, root, inode, start, aligned_end, 1);
	if (ret)
		return ret;

	if (isize > actual_end)
		inline_len = min_t(u64, isize, actual_end);
	ret = insert_inline_extent(trans, root, inode, start,
				   inline_len, compressed_size,
				   compress_type, compressed_pages);
	if (ret && ret != -ENOSPC) {
		btrfs_abort_transaction(trans, root, ret);
		return ret;
	} else if (ret == -ENOSPC) {
		return 1;
	}

	btrfs_delalloc_release_metadata(inode, end + 1 - start);
	btrfs_drop_extent_cache(inode, start, aligned_end - 1, 0);
	return 0;
}

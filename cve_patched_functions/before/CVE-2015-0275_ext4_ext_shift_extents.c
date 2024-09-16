ext4_ext_shift_extents(struct inode *inode, handle_t *handle,
		       ext4_lblk_t start, ext4_lblk_t shift)
{
	struct ext4_ext_path *path;
	int ret = 0, depth;
	struct ext4_extent *extent;
	ext4_lblk_t stop_block;
	ext4_lblk_t ex_start, ex_end;

	/* Let path point to the last extent */
	path = ext4_find_extent(inode, EXT_MAX_BLOCKS - 1, NULL, 0);
	if (IS_ERR(path))
		return PTR_ERR(path);

	depth = path->p_depth;
	extent = path[depth].p_ext;
	if (!extent)
		goto out;

	stop_block = le32_to_cpu(extent->ee_block) +
			ext4_ext_get_actual_len(extent);

	/* Nothing to shift, if hole is at the end of file */
	if (start >= stop_block)
		goto out;

	/*
	 * Don't start shifting extents until we make sure the hole is big
	 * enough to accomodate the shift.
	 */
	path = ext4_find_extent(inode, start - 1, &path, 0);
	if (IS_ERR(path))
		return PTR_ERR(path);
	depth = path->p_depth;
	extent =  path[depth].p_ext;
	if (extent) {
		ex_start = le32_to_cpu(extent->ee_block);
		ex_end = le32_to_cpu(extent->ee_block) +
			ext4_ext_get_actual_len(extent);
	} else {
		ex_start = 0;
		ex_end = 0;
	}

	if ((start == ex_start && shift > ex_start) ||
	    (shift > start - ex_end))
		return -EINVAL;

	/* Its safe to start updating extents */
	while (start < stop_block) {
		path = ext4_find_extent(inode, start, &path, 0);
		if (IS_ERR(path))
			return PTR_ERR(path);
		depth = path->p_depth;
		extent = path[depth].p_ext;
		if (!extent) {
			EXT4_ERROR_INODE(inode, "unexpected hole at %lu",
					 (unsigned long) start);
			return -EIO;
		}
		if (start > le32_to_cpu(extent->ee_block)) {
			/* Hole, move to the next extent */
			if (extent < EXT_LAST_EXTENT(path[depth].p_hdr)) {
				path[depth].p_ext++;
			} else {
				start = ext4_ext_next_allocated_block(path);
				continue;
			}
		}
		ret = ext4_ext_shift_path_extents(path, shift, inode,
				handle, &start);
		if (ret)
			break;
	}
out:
	ext4_ext_drop_refs(path);
	kfree(path);
	return ret;
}

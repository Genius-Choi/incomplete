ext4_ext_shift_path_extents(struct ext4_ext_path *path, ext4_lblk_t shift,
			    struct inode *inode, handle_t *handle,
			    ext4_lblk_t *start)
{
	int depth, err = 0;
	struct ext4_extent *ex_start, *ex_last;
	bool update = 0;
	depth = path->p_depth;

	while (depth >= 0) {
		if (depth == path->p_depth) {
			ex_start = path[depth].p_ext;
			if (!ex_start)
				return -EIO;

			ex_last = EXT_LAST_EXTENT(path[depth].p_hdr);

			err = ext4_access_path(handle, inode, path + depth);
			if (err)
				goto out;

			if (ex_start == EXT_FIRST_EXTENT(path[depth].p_hdr))
				update = 1;

			*start = le32_to_cpu(ex_last->ee_block) +
				ext4_ext_get_actual_len(ex_last);

			while (ex_start <= ex_last) {
				le32_add_cpu(&ex_start->ee_block, -shift);
				/* Try to merge to the left. */
				if ((ex_start >
				     EXT_FIRST_EXTENT(path[depth].p_hdr)) &&
				    ext4_ext_try_to_merge_right(inode,
							path, ex_start - 1))
					ex_last--;
				else
					ex_start++;
			}
			err = ext4_ext_dirty(handle, inode, path + depth);
			if (err)
				goto out;

			if (--depth < 0 || !update)
				break;
		}

		/* Update index too */
		err = ext4_access_path(handle, inode, path + depth);
		if (err)
			goto out;

		le32_add_cpu(&path[depth].p_idx->ei_block, -shift);
		err = ext4_ext_dirty(handle, inode, path + depth);
		if (err)
			goto out;

		/* we are done if current index is not a starting index */
		if (path[depth].p_idx != EXT_FIRST_INDEX(path[depth].p_hdr))
			break;

		depth--;
	}

out:
	return err;
}

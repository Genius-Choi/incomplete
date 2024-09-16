int ext4_ext_index_trans_blocks(struct inode *inode, int extents)
{
	int index;
	int depth;

	/* If we are converting the inline data, only one is needed here. */
	if (ext4_has_inline_data(inode))
		return 1;

	depth = ext_depth(inode);

	if (extents <= 1)
		index = depth * 2;
	else
		index = depth * 3;

	return index;
}

static int lookup_metapath(struct gfs2_inode *ip, struct metapath *mp)
{
	unsigned int end_of_metadata = ip->i_height - 1;
	unsigned int x;
	__be64 *ptr;
	u64 dblock;
	int ret;

	for (x = 0; x < end_of_metadata; x++) {
		ptr = metapointer(x, mp);
		dblock = be64_to_cpu(*ptr);
		if (!dblock)
			return x + 1;

		ret = gfs2_meta_indirect_buffer(ip, x+1, dblock, 0, &mp->mp_bh[x+1]);
		if (ret)
			return ret;
	}

	return ip->i_height;
}

static int trunc_dealloc(struct gfs2_inode *ip, u64 size)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	unsigned int height = ip->i_height;
	u64 lblock;
	struct metapath mp;
	int error;

	if (!size)
		lblock = 0;
	else
		lblock = (size - 1) >> sdp->sd_sb.sb_bsize_shift;

	find_metapath(sdp, lblock, &mp, ip->i_height);
	if (!gfs2_alloc_get(ip))
		return -ENOMEM;

	error = gfs2_quota_hold(ip, NO_QUOTA_CHANGE, NO_QUOTA_CHANGE);
	if (error)
		goto out;

	while (height--) {
		struct strip_mine sm;
		sm.sm_first = !!size;
		sm.sm_height = height;

		error = recursive_scan(ip, NULL, &mp, 0, 0, 1, &sm);
		if (error)
			break;
	}

	gfs2_quota_unhold(ip);

out:
	gfs2_alloc_put(ip);
	return error;
}

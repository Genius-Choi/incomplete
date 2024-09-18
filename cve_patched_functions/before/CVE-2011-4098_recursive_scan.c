static int recursive_scan(struct gfs2_inode *ip, struct buffer_head *dibh,
			  struct metapath *mp, unsigned int height,
			  u64 block, int first, struct strip_mine *sm)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct buffer_head *bh = NULL;
	__be64 *top, *bottom, *t2;
	u64 bn;
	int error;
	int mh_size = sizeof(struct gfs2_meta_header);

	if (!height) {
		error = gfs2_meta_inode_buffer(ip, &bh);
		if (error)
			return error;
		dibh = bh;

		top = (__be64 *)(bh->b_data + sizeof(struct gfs2_dinode)) + mp->mp_list[0];
		bottom = (__be64 *)(bh->b_data + sizeof(struct gfs2_dinode)) + sdp->sd_diptrs;
	} else {
		error = gfs2_meta_indirect_buffer(ip, height, block, 0, &bh);
		if (error)
			return error;

		top = (__be64 *)(bh->b_data + mh_size) +
				  (first ? mp->mp_list[height] : 0);

		bottom = (__be64 *)(bh->b_data + mh_size) + sdp->sd_inptrs;
	}

	error = do_strip(ip, dibh, bh, top, bottom, height, sm);
	if (error)
		goto out;

	if (height < ip->i_height - 1) {
		struct buffer_head *rabh;

		for (t2 = top; t2 < bottom; t2++, first = 0) {
			if (!*t2)
				continue;

			bn = be64_to_cpu(*t2);
			rabh = gfs2_getbuf(ip->i_gl, bn, CREATE);
			if (trylock_buffer(rabh)) {
				if (buffer_uptodate(rabh)) {
					unlock_buffer(rabh);
					brelse(rabh);
					continue;
				}
				rabh->b_end_io = end_buffer_read_sync;
				submit_bh(READA | REQ_META, rabh);
				continue;
			}
			brelse(rabh);
		}
		for (; top < bottom; top++, first = 0) {
			if (!*top)
				continue;

			bn = be64_to_cpu(*top);

			error = recursive_scan(ip, dibh, mp, height + 1, bn,
					       first, sm);
			if (error)
				break;
		}
	}
out:
	brelse(bh);
	return error;
}

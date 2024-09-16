static inline __be64 *metapointer(unsigned int height, const struct metapath *mp)
{
	struct buffer_head *bh = mp->mp_bh[height];
	unsigned int head_size = (height > 0) ?
		sizeof(struct gfs2_meta_header) : sizeof(struct gfs2_dinode);
	return ((__be64 *)(bh->b_data + head_size)) + mp->mp_list[height];
}

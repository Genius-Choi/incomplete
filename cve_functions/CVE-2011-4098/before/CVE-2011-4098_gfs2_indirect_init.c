static inline __be64 *gfs2_indirect_init(struct metapath *mp,
					 struct gfs2_glock *gl, unsigned int i,
					 unsigned offset, u64 bn)
{
	__be64 *ptr = (__be64 *)(mp->mp_bh[i - 1]->b_data +
		       ((i > 1) ? sizeof(struct gfs2_meta_header) :
				 sizeof(struct gfs2_dinode)));
	BUG_ON(i < 1);
	BUG_ON(mp->mp_bh[i] != NULL);
	mp->mp_bh[i] = gfs2_meta_new(gl, bn);
	gfs2_trans_add_bh(gl, mp->mp_bh[i], 1);
	gfs2_metatype_set(mp->mp_bh[i], GFS2_METATYPE_IN, GFS2_FORMAT_IN);
	gfs2_buffer_clear_tail(mp->mp_bh[i], sizeof(struct gfs2_meta_header));
	ptr += offset;
	*ptr = cpu_to_be64(bn);
	return ptr;
}

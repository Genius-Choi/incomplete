static int multipath_end_io(struct dm_target *ti, struct request *clone,
			    int error, union map_info *map_context)
{
	struct multipath *m = ti->private;
	struct dm_mpath_io *mpio = map_context->ptr;
	struct pgpath *pgpath = mpio->pgpath;
	struct path_selector *ps;
	int r;

	r  = do_end_io(m, clone, error, mpio);
	if (pgpath) {
		ps = &pgpath->pg->ps;
		if (ps->type->end_io)
			ps->type->end_io(ps, &pgpath->path, mpio->nr_bytes);
	}
	mempool_free(mpio, m->mpio_pool);

	return r;
}

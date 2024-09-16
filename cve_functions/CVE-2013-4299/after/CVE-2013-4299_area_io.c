static int area_io(struct pstore *ps, int rw)
{
	int r;
	chunk_t chunk;

	chunk = area_location(ps, ps->current_area);

	r = chunk_io(ps, ps->area, chunk, rw, 0);
	if (r)
		return r;

	return 0;
}

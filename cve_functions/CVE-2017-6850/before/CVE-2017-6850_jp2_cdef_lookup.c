jp2_cdefchan_t *jp2_cdef_lookup(jp2_cdef_t *cdef, int channo)
{
	unsigned int i;
	jp2_cdefchan_t *cdefent;
	for (i = 0; i < cdef->numchans; ++i) {
		cdefent = &cdef->ents[i];
		if (cdefent->channo == JAS_CAST(unsigned int, channo)) {
			return cdefent;
		}
	}
	return 0;
}

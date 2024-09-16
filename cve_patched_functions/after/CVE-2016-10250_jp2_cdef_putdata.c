static int jp2_cdef_putdata(jp2_box_t *box, jas_stream_t *out)
{
	jp2_cdef_t *cdef = &box->data.cdef;
	unsigned int i;
	jp2_cdefchan_t *ent;

	if (jp2_putuint16(out, cdef->numchans)) {
		return -1;
	}

	for (i = 0; i < cdef->numchans; ++i) {
		ent = &cdef->ents[i];
		if (jp2_putuint16(out, ent->channo) ||
		  jp2_putuint16(out, ent->type) ||
		  jp2_putuint16(out, ent->assoc)) {
			return -1;
		}
	}
	return 0;
}

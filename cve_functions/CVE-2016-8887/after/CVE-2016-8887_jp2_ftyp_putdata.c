static int jp2_ftyp_putdata(jp2_box_t *box, jas_stream_t *out)
{
	jp2_ftyp_t *ftyp = &box->data.ftyp;
	unsigned int i;
	if (jp2_putuint32(out, ftyp->majver) || jp2_putuint32(out, ftyp->minver)) {
		return -1;
	}
	for (i = 0; i < ftyp->numcompatcodes; ++i) {
		if (jp2_putuint32(out, ftyp->compatcodes[i])) {
			return -1;
		}
	}
	return 0;
}

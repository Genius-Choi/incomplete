static int jp2_ftyp_getdata(jp2_box_t *box, jas_stream_t *in)
{
	jp2_ftyp_t *ftyp = &box->data.ftyp;
	unsigned int i;
	if (jp2_getuint32(in, &ftyp->majver) || jp2_getuint32(in, &ftyp->minver)) {
		return -1;
	}
	ftyp->numcompatcodes = (box->datalen - 8) / 4;
	if (ftyp->numcompatcodes > JP2_FTYP_MAXCOMPATCODES) {
		return -1;
	}
	for (i = 0; i < ftyp->numcompatcodes; ++i) {
		if (jp2_getuint32(in, &ftyp->compatcodes[i])) {
			return -1;
		}
	}
	return 0;
}

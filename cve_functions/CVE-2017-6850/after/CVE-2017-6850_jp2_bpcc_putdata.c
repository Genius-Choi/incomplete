static int jp2_bpcc_putdata(jp2_box_t *box, jas_stream_t *out)
{
	jp2_bpcc_t *bpcc = &box->data.bpcc;
	unsigned int i;
	for (i = 0; i < bpcc->numcmpts; ++i) {
		if (jp2_putuint8(out, bpcc->bpcs[i])) {
			return -1;
		}
	}
	return 0;
}

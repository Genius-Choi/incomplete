static int jp2_jp_putdata(jp2_box_t *box, jas_stream_t *out)
{
	jp2_jp_t *jp = &box->data.jp;
	if (jp2_putuint32(out, jp->magic)) {
		return -1;
	}
	return 0;
}

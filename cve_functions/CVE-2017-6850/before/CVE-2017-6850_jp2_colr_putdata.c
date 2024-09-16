static int jp2_colr_putdata(jp2_box_t *box, jas_stream_t *out)
{
	jp2_colr_t *colr = &box->data.colr;
	if (jp2_putuint8(out, colr->method) || jp2_putuint8(out, colr->pri) ||
	  jp2_putuint8(out, colr->approx)) {
		return -1;
	}
	switch (colr->method) {
	case JP2_COLR_ENUM:
		if (jp2_putuint32(out, colr->csid)) {
			return -1;
		}
		break;
	case JP2_COLR_ICC:
		if (jas_stream_write(out, colr->iccp,
		  JAS_CAST(int, colr->iccplen)) != JAS_CAST(int, colr->iccplen))
			return -1;
		break;
	}
	return 0;
}

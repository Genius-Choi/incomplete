static int jp2_ihdr_getdata(jp2_box_t *box, jas_stream_t *in)
{
	jp2_ihdr_t *ihdr = &box->data.ihdr;
	if (jp2_getuint32(in, &ihdr->height) || jp2_getuint32(in, &ihdr->width) ||
	  jp2_getuint16(in, &ihdr->numcmpts) || jp2_getuint8(in, &ihdr->bpc) ||
	  jp2_getuint8(in, &ihdr->comptype) || jp2_getuint8(in, &ihdr->csunk) ||
	  jp2_getuint8(in, &ihdr->ipr)) {
		return -1;
	}
	return 0;
}

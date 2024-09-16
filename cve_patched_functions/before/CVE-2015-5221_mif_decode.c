jas_image_t *mif_decode(jas_stream_t *in, char *optstr)
{
	mif_hdr_t *hdr;
	jas_image_t *image;
	jas_image_t *tmpimage;
	jas_stream_t *tmpstream;
	int cmptno;
	mif_cmpt_t *cmpt;
	jas_image_cmptparm_t cmptparm;
	jas_seq2d_t *data;
	int_fast32_t x;
	int_fast32_t y;
	int bias;

	/* Avoid warnings about unused parameters. */
	optstr = 0;

	hdr = 0;
	image = 0;
	tmpimage = 0;
	tmpstream = 0;
	data = 0;

	if (!(hdr = mif_hdr_get(in))) {
		goto error;
	}

	if (!(image = jas_image_create0())) {
		goto error;
	}

	for (cmptno = 0; cmptno < hdr->numcmpts; ++cmptno) {
		cmpt = hdr->cmpts[cmptno];
		tmpstream = cmpt->data ? jas_stream_fopen(cmpt->data, "rb") : in;
		if (!tmpstream) {
			goto error;
		}
		if (!(tmpimage = jas_image_decode(tmpstream, -1, 0))) {
			goto error;
		}
		if (tmpstream != in) {
			jas_stream_close(tmpstream);
			tmpstream = 0;
		}
		if (!cmpt->width) {
			cmpt->width = jas_image_cmptwidth(tmpimage, 0);
		}
		if (!cmpt->height) {
			cmpt->height = jas_image_cmptwidth(tmpimage, 0);
		}
		if (!cmpt->prec) {
			cmpt->prec = jas_image_cmptprec(tmpimage, 0);
		}
		if (cmpt->sgnd < 0) {
			cmpt->sgnd = jas_image_cmptsgnd(tmpimage, 0);
		}
		cmptparm.tlx = cmpt->tlx;
		cmptparm.tly = cmpt->tly;
		cmptparm.hstep = cmpt->sampperx;
		cmptparm.vstep = cmpt->samppery;
		cmptparm.width = cmpt->width;
		cmptparm.height = cmpt->height;
		cmptparm.prec = cmpt->prec;
		cmptparm.sgnd = cmpt->sgnd;
		if (jas_image_addcmpt(image, jas_image_numcmpts(image), &cmptparm)) {
			goto error;
		}
		if (!(data = jas_seq2d_create(0, 0, cmpt->width, cmpt->height))) {
			goto error;
		}
		if (jas_image_readcmpt(tmpimage, 0, 0, 0, cmpt->width, cmpt->height,
		  data)) {
			goto error;
		}
		if (cmpt->sgnd) {
			bias = 1 << (cmpt->prec - 1);
			for (y = 0; y < cmpt->height; ++y) {
				for (x = 0; x < cmpt->width; ++x) {
					*jas_seq2d_getref(data, x, y) -= bias;
				}
			}
		}
		if (jas_image_writecmpt(image, jas_image_numcmpts(image) - 1, 0, 0,
		  cmpt->width, cmpt->height, data)) {
			goto error;
		}
		jas_seq2d_destroy(data);
		data = 0;
		jas_image_destroy(tmpimage);
		tmpimage = 0;
	}

	mif_hdr_destroy(hdr);
	hdr = 0;
	return image;

error:
	if (image) {
		jas_image_destroy(image);
	}
	if (hdr) {
		mif_hdr_destroy(hdr);
	}
	if (tmpstream && tmpstream != in) {
		jas_stream_close(tmpstream);
	}
	if (tmpimage) {
		jas_image_destroy(tmpimage);
	}
	if (data) {
		jas_seq2d_destroy(data);
	}
	return 0;
}

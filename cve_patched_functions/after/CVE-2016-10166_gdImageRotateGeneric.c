gdImageRotateGeneric(gdImagePtr src, const float degrees, const int bgColor)
{
	float _angle = ((float) (-degrees / 180.0f) * (float)M_PI);
	const int src_w  = gdImageSX(src);
	const int src_h = gdImageSY(src);
	const gdFixed f_H = gd_itofx(src_h/2);
	const gdFixed f_W = gd_itofx(src_w/2);
	const gdFixed f_cos = gd_ftofx(cos(-_angle));
	const gdFixed f_sin = gd_ftofx(sin(-_angle));

	unsigned int dst_offset_x;
	unsigned int dst_offset_y = 0;
	unsigned int i;
	gdImagePtr dst;
	int new_width, new_height;
	gdRect bbox;

	if (bgColor < 0) {
		return NULL;
	}

	if (src->interpolation == NULL) {
		gdImageSetInterpolationMethod(src, GD_DEFAULT);
	}

    gdRotatedImageSize(src, degrees, &bbox);
    new_width = bbox.width;
    new_height = bbox.height;

	dst = gdImageCreateTrueColor(new_width, new_height);
	if (!dst) {
		return NULL;
	}
	dst->saveAlphaFlag = 1;

	for (i = 0; i < new_height; i++) {
		unsigned int j;
		dst_offset_x = 0;
		for (j = 0; j < new_width; j++) {
			gdFixed f_i = gd_itofx((int)i - (int)new_height / 2);
			gdFixed f_j = gd_itofx((int)j - (int)new_width  / 2);
			gdFixed f_m = gd_mulfx(f_j,f_sin) + gd_mulfx(f_i,f_cos) + f_H;
			gdFixed f_n = gd_mulfx(f_j,f_cos) - gd_mulfx(f_i,f_sin)  + f_W;
			long m = gd_fxtoi(f_m);
			long n = gd_fxtoi(f_n);

			if (m < -1 || n < -1 || m >= src_h || n >= src_w ) {
				dst->tpixels[dst_offset_y][dst_offset_x++] = bgColor;
			} else {
				dst->tpixels[dst_offset_y][dst_offset_x++] = getPixelInterpolated(src, gd_fxtod(f_n), gd_fxtod(f_m), bgColor);
			}
		}
		dst_offset_y++;
	}
	return dst;
}

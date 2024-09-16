static void bmpr_strip_alpha(struct iw_image *img)
{
	int i,j;
	size_t oldbpr;

	img->imgtype = IW_IMGTYPE_RGB;
	oldbpr = img->bpr;
	img->bpr = iw_calc_bytesperrow(img->width,24);

	for(j=0;j<img->height;j++) {
		for(i=0;i<img->width;i++) {
			img->pixels[j*img->bpr + i*3 + 0] = img->pixels[j*oldbpr + i*4 + 0];
			img->pixels[j*img->bpr + i*3 + 1] = img->pixels[j*oldbpr + i*4 + 1];
			img->pixels[j*img->bpr + i*3 + 2] = img->pixels[j*oldbpr + i*4 + 2];
		}
	}
}

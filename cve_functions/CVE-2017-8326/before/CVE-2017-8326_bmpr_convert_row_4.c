static void bmpr_convert_row_4(struct iwbmprcontext *rctx,const iw_byte *src, size_t row)
{
	int i;
	int pal_index;

	for(i=0;i<rctx->width;i++) {
		pal_index = (i&0x1) ? src[i/2]&0x0f : src[i/2]>>4;
		rctx->img->pixels[row*rctx->img->bpr + i*3 + 0] = rctx->palette.entry[pal_index].r;
		rctx->img->pixels[row*rctx->img->bpr + i*3 + 1] = rctx->palette.entry[pal_index].g;
		rctx->img->pixels[row*rctx->img->bpr + i*3 + 2] = rctx->palette.entry[pal_index].b;
	}
}

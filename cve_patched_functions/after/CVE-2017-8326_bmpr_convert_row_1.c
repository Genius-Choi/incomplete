static void bmpr_convert_row_1(struct iwbmprcontext *rctx,const iw_byte *src, size_t row)
{
	int i;
	int pal_index;

	for(i=0;i<rctx->width;i++) {
		pal_index = (src[i/8] & (1<<(7-i%8))) ? 1 : 0;
		rctx->img->pixels[row*rctx->img->bpr + i*3 + 0] = rctx->palette.entry[pal_index].r;
		rctx->img->pixels[row*rctx->img->bpr + i*3 + 1] = rctx->palette.entry[pal_index].g;
		rctx->img->pixels[row*rctx->img->bpr + i*3 + 2] = rctx->palette.entry[pal_index].b;
	}
}

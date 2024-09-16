static void bmpr_convert_row_8(struct iwbmprcontext *rctx,const iw_byte *src, size_t row)
{
	int i;
	for(i=0;i<rctx->width;i++) {
		rctx->img->pixels[row*rctx->img->bpr + i*3 + 0] = rctx->palette.entry[src[i]].r;
		rctx->img->pixels[row*rctx->img->bpr + i*3 + 1] = rctx->palette.entry[src[i]].g;
		rctx->img->pixels[row*rctx->img->bpr + i*3 + 2] = rctx->palette.entry[src[i]].b;
	}
}

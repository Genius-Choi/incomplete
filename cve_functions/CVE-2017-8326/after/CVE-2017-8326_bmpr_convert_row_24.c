static void bmpr_convert_row_24(struct iwbmprcontext *rctx,const iw_byte *src, size_t row)
{
	int i;
	for(i=0;i<rctx->width;i++) {
		rctx->img->pixels[row*rctx->img->bpr + i*3 + 0] = src[i*3+2];
		rctx->img->pixels[row*rctx->img->bpr + i*3 + 1] = src[i*3+1];
		rctx->img->pixels[row*rctx->img->bpr + i*3 + 2] = src[i*3+0];
	}
}

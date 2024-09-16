static void iwbmp_write_pixels_uncompressed(struct iwbmpwcontext *wctx,
	struct iw_image *img)
{
	int j;
	iw_byte *dstrow = NULL;
	const iw_byte *srcrow;

	dstrow = iw_mallocz(wctx->ctx,wctx->unc_dst_bpr);
	if(!dstrow) goto done;

	for(j=img->height-1;j>=0;j--) {
		srcrow = &img->pixels[j*img->bpr];
		switch(wctx->bitcount) {
		case 32: bmpw_convert_row_16_32(wctx,srcrow,dstrow,img->width); break;
		case 24: bmpw_convert_row_24(wctx,srcrow,dstrow,img->width); break;
		case 16: bmpw_convert_row_16_32(wctx,srcrow,dstrow,img->width); break;
		case 8: bmpw_convert_row_8(srcrow,dstrow,img->width); break;
		case 4: bmpw_convert_row_4(srcrow,dstrow,img->width); break;
		case 1: bmpw_convert_row_1(srcrow,dstrow,img->width); break;
		}
		iwbmp_write(wctx,dstrow,wctx->unc_dst_bpr);
	}

done:
	if(dstrow) iw_free(wctx->ctx,dstrow);
	return;
}

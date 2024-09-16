static int iwbmp_write_bmp_header(struct iwbmpwcontext *wctx)
{
	if(wctx->bmpversion==2) {
		return iwbmp_write_bmp_v2header(wctx);
	}
	else if(wctx->bmpversion==5) {
		if(!iwbmp_write_bmp_v3header(wctx)) return 0;
		return iwbmp_write_bmp_v45header_fields(wctx);
	}
	return iwbmp_write_bmp_v3header(wctx);
}

IW_IMPL(void) iw_set_bkgd_checkerboard(struct iw_context *ctx, int checkersize,
    double r2, double g2, double b2)
{
	struct iw_color clr;
	clr.c[IW_CHANNELTYPE_RED]=r2;
	clr.c[IW_CHANNELTYPE_GREEN]=g2;
	clr.c[IW_CHANNELTYPE_BLUE]=b2;
	clr.c[IW_CHANNELTYPE_ALPHA]=1.0;
	iw_set_bkgd_checkerboard_2(ctx, checkersize, &clr);
}

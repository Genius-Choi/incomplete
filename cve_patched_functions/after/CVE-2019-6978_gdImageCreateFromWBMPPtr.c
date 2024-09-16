gdImagePtr gdImageCreateFromWBMPPtr (int size, void *data)
{
	gdImagePtr im;
	gdIOCtx *in = gdNewDynamicCtxEx(size, data, 0);
	im = gdImageCreateFromWBMPCtx(in);
	in->gd_free(in);
	return im;
}

gdImagePtr gdImageCreateFromJpegPtrEx (int size, void *data, int ignore_warning)
{
	gdImagePtr im;
	gdIOCtx *in = gdNewDynamicCtxEx(size, data, 0);
	im = gdImageCreateFromJpegCtxEx(in, ignore_warning);
	in->gd_free(in);

	return im;
}

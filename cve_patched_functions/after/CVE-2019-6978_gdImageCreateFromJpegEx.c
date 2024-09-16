gdImagePtr gdImageCreateFromJpegEx (FILE * inFile, int ignore_warning)
{
	gdImagePtr im;
	gdIOCtx *in = gdNewFileCtx(inFile);
	im = gdImageCreateFromJpegCtxEx(in, ignore_warning);
	in->gd_free (in);

	return im;
}

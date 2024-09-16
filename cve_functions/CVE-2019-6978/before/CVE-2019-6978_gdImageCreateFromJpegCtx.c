gdImagePtr gdImageCreateFromJpegCtx (gdIOCtx * infile)
{
	return gdImageCreateFromJpegCtxEx(infile, 1);
}

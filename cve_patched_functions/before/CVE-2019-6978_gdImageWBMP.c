void gdImageWBMP (gdImagePtr im, int fg, FILE * outFile)
{
	gdIOCtx *out = gdNewFileCtx(outFile);
	gdImageWBMPCtx(im, fg, out);
	out->gd_free(out);
}

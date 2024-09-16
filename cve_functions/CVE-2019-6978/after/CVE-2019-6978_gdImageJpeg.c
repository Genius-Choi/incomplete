void gdImageJpeg (gdImagePtr im, FILE * outFile, int quality)
{
	gdIOCtx *out = gdNewFileCtx (outFile);
	gdImageJpegCtx (im, out, quality);
	out->gd_free (out);
}

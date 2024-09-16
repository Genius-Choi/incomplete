BGD_DECLARE(void) gdImageTiffCtx(gdImagePtr image, gdIOCtx *out)
{
	int clipx1P, clipy1P, clipx2P, clipy2P;
	int bitDepth = 24;

	/* First, switch off clipping, or we'll not get all the image! */
	gdImageGetClip(image, &clipx1P, &clipy1P, &clipx2P, &clipy2P);

	/* use the appropriate routine depending on the bit depth of the image */
	if(image->trueColor) {
		bitDepth = 24;
	} else if(image->colorsTotal == 2) {
		bitDepth = 1;
	} else {
		bitDepth = 8;
	}

	tiffWriter(image, out, bitDepth);

	/* reset clipping area to the gd image's original values */
	gdImageSetClip(image, clipx1P, clipy1P, clipx2P, clipy2P);
}

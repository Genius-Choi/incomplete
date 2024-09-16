TIFFComputeStrip(TIFF* tif, uint32 row, uint16 sample)
{
	static const char module[] = "TIFFComputeStrip";
	TIFFDirectory *td = &tif->tif_dir;
	uint32 strip;

	strip = row / td->td_rowsperstrip;
	if (td->td_planarconfig == PLANARCONFIG_SEPARATE) {
		if (sample >= td->td_samplesperpixel) {
			TIFFErrorExt(tif->tif_clientdata, module,
			    "%lu: Sample out of range, max %lu",
			    (unsigned long) sample, (unsigned long) td->td_samplesperpixel);
			return (0);
		}
		strip += (uint32)sample*td->td_stripsperimage;
	}
	return (strip);
}

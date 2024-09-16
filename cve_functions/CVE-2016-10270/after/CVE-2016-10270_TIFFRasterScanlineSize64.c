TIFFRasterScanlineSize64(TIFF* tif)
{
	static const char module[] = "TIFFRasterScanlineSize64";
	TIFFDirectory *td = &tif->tif_dir;
	uint64 scanline;

	scanline = _TIFFMultiply64(tif, td->td_bitspersample, td->td_imagewidth, module);
	if (td->td_planarconfig == PLANARCONFIG_CONTIG) {
		scanline = _TIFFMultiply64(tif, scanline, td->td_samplesperpixel, module);
		return (TIFFhowmany8_64(scanline));
	} else
		return (_TIFFMultiply64(tif, TIFFhowmany8_64(scanline),
		    td->td_samplesperpixel, module));
}

TIFFScanlineSize(TIFF* tif)
{
	static const char module[] = "TIFFScanlineSize";
	uint64 m;
	tmsize_t n;
	m=TIFFScanlineSize64(tif);
	n=(tmsize_t)m;
	if ((uint64)n!=m) {
		TIFFErrorExt(tif->tif_clientdata,module,"Integer arithmetic overflow");
		n=0;
	}
	return(n);
}

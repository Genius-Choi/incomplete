TIFFStripSize(TIFF* tif)
{
	static const char module[] = "TIFFStripSize";
	uint64 m;
	tmsize_t n;
	m=TIFFStripSize64(tif);
	n=(tmsize_t)m;
	if ((uint64)n!=m)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"Integer overflow");
		n=0;
	}
	return(n);
}

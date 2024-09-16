TIFFRawStripSize(TIFF* tif, uint32 strip)
{
	static const char module[] = "TIFFRawStripSize";
	uint64 m;
	tmsize_t n;
	m=TIFFRawStripSize64(tif,strip);
	if (m==(uint64)(-1))
		n=(tmsize_t)(-1);
	else
	{
		n=(tmsize_t)m;
		if ((uint64)n!=m)
		{
			TIFFErrorExt(tif->tif_clientdata,module,"Integer overflow");
			n=0;
		}
	}
	return(n);
}

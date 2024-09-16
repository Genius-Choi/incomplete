TIFFVStripSize(TIFF* tif, uint32 nrows)
{
	static const char module[] = "TIFFVStripSize";
	uint64 m;
	tmsize_t n;
	m=TIFFVStripSize64(tif,nrows);
	n=(tmsize_t)m;
	if ((uint64)n!=m)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"Integer overflow");
		n=0;
	}
	return(n);
}

OJPEGDecodeScanlines(TIFF* tif, uint8* buf, tmsize_t cc)
{
	static const char module[]="OJPEGDecodeScanlines";
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	uint8* m;
	tmsize_t n;
	if (cc%sp->bytes_per_line!=0)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"Fractional scanline not read");
		return(0);
	}
	assert(cc>0);
	m=buf;
	n=cc;
	do
	{
		if (jpeg_read_scanlines_encap(sp,&(sp->libjpeg_jpeg_decompress_struct),&m,1)==0)
			return(0);
		m+=sp->bytes_per_line;
		n-=sp->bytes_per_line;
	} while(n>0);
	return(1);
}

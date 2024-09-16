OJPEGPreDecodeSkipScanlines(TIFF* tif)
{
	static const char module[]="OJPEGPreDecodeSkipScanlines";
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	uint32 m;
	if (sp->skip_buffer==NULL)
	{
		sp->skip_buffer=_TIFFmalloc(sp->bytes_per_line);
		if (sp->skip_buffer==NULL)
		{
			TIFFErrorExt(tif->tif_clientdata,module,"Out of memory");
			return(0);
		}
	}
	for (m=0; m<sp->lines_per_strile; m++)
	{
		if (jpeg_read_scanlines_encap(sp,&(sp->libjpeg_jpeg_decompress_struct),&sp->skip_buffer,1)==0)
			return(0);
	}
	return(1);
}

OJPEGPreDecodeSkipRaw(TIFF* tif)
{
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	uint32 m;
	m=sp->lines_per_strile;
	if (sp->subsampling_convert_state!=0)
	{
		if (sp->subsampling_convert_clines-sp->subsampling_convert_state>=m)
		{
			sp->subsampling_convert_state+=m;
			if (sp->subsampling_convert_state==sp->subsampling_convert_clines)
				sp->subsampling_convert_state=0;
			return(1);
		}
		m-=sp->subsampling_convert_clines-sp->subsampling_convert_state;
		sp->subsampling_convert_state=0;
	}
	while (m>=sp->subsampling_convert_clines)
	{
		if (jpeg_read_raw_data_encap(sp,&(sp->libjpeg_jpeg_decompress_struct),sp->subsampling_convert_ycbcrimage,sp->subsampling_ver*8)==0)
			return(0);
		m-=sp->subsampling_convert_clines;
	}
	if (m>0)
	{
		if (jpeg_read_raw_data_encap(sp,&(sp->libjpeg_jpeg_decompress_struct),sp->subsampling_convert_ycbcrimage,sp->subsampling_ver*8)==0)
			return(0);
		sp->subsampling_convert_state=m;
	}
	return(1);
}

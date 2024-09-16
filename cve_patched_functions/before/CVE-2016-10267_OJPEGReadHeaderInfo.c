OJPEGReadHeaderInfo(TIFF* tif)
{
	static const char module[]="OJPEGReadHeaderInfo";
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	assert(sp->readheader_done==0);
	sp->image_width=tif->tif_dir.td_imagewidth;
	sp->image_length=tif->tif_dir.td_imagelength;
	if isTiled(tif)
	{
		sp->strile_width=tif->tif_dir.td_tilewidth;
		sp->strile_length=tif->tif_dir.td_tilelength;
		sp->strile_length_total=((sp->image_length+sp->strile_length-1)/sp->strile_length)*sp->strile_length;
	}
	else
	{
		sp->strile_width=sp->image_width;
		sp->strile_length=tif->tif_dir.td_rowsperstrip;
		sp->strile_length_total=sp->image_length;
	}
	if (tif->tif_dir.td_samplesperpixel==1)
	{
		sp->samples_per_pixel=1;
		sp->plane_sample_offset=0;
		sp->samples_per_pixel_per_plane=sp->samples_per_pixel;
		sp->subsampling_hor=1;
		sp->subsampling_ver=1;
	}
	else
	{
		if (tif->tif_dir.td_samplesperpixel!=3)
		{
			TIFFErrorExt(tif->tif_clientdata,module,"SamplesPerPixel %d not supported for this compression scheme",sp->samples_per_pixel);
			return(0);
		}
		sp->samples_per_pixel=3;
		sp->plane_sample_offset=0;
		if (tif->tif_dir.td_planarconfig==PLANARCONFIG_CONTIG)
			sp->samples_per_pixel_per_plane=3;
		else
			sp->samples_per_pixel_per_plane=1;
	}
	if (sp->strile_length<sp->image_length)
	{
		if (sp->strile_length%(sp->subsampling_ver*8)!=0)
		{
			TIFFErrorExt(tif->tif_clientdata,module,"Incompatible vertical subsampling and image strip/tile length");
			return(0);
		}
		sp->restart_interval=(uint16)(((sp->strile_width+sp->subsampling_hor*8-1)/(sp->subsampling_hor*8))*(sp->strile_length/(sp->subsampling_ver*8)));
	}
	if (OJPEGReadHeaderInfoSec(tif)==0)
		return(0);
	sp->sos_end[0].log=1;
	sp->sos_end[0].in_buffer_source=sp->in_buffer_source;
	sp->sos_end[0].in_buffer_next_strile=sp->in_buffer_next_strile;
	sp->sos_end[0].in_buffer_file_pos=sp->in_buffer_file_pos-sp->in_buffer_togo;
	sp->sos_end[0].in_buffer_file_togo=sp->in_buffer_file_togo+sp->in_buffer_togo; 
	sp->readheader_done=1;
	return(1);
}

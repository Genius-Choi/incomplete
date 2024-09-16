OJPEGSubsamplingCorrect(TIFF* tif)
{
	static const char module[]="OJPEGSubsamplingCorrect";
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	uint8 mh;
	uint8 mv;
        _TIFFFillStriles( tif );
        
	assert(sp->subsamplingcorrect_done==0);
	if ((tif->tif_dir.td_samplesperpixel!=3) || ((tif->tif_dir.td_photometric!=PHOTOMETRIC_YCBCR) &&
	    (tif->tif_dir.td_photometric!=PHOTOMETRIC_ITULAB)))
	{
		if (sp->subsampling_tag!=0)
			TIFFWarningExt(tif->tif_clientdata,module,"Subsampling tag not appropriate for this Photometric and/or SamplesPerPixel");
		sp->subsampling_hor=1;
		sp->subsampling_ver=1;
		sp->subsampling_force_desubsampling_inside_decompression=0;
	}
	else
	{
		sp->subsamplingcorrect_done=1;
		mh=sp->subsampling_hor;
		mv=sp->subsampling_ver;
		sp->subsamplingcorrect=1;
		OJPEGReadHeaderInfoSec(tif);
		if (sp->subsampling_force_desubsampling_inside_decompression!=0)
		{
			sp->subsampling_hor=1;
			sp->subsampling_ver=1;
		}
		sp->subsamplingcorrect=0;
		if (((sp->subsampling_hor!=mh) || (sp->subsampling_ver!=mv)) && (sp->subsampling_force_desubsampling_inside_decompression==0))
		{
			if (sp->subsampling_tag==0)
				TIFFWarningExt(tif->tif_clientdata,module,"Subsampling tag is not set, yet subsampling inside JPEG data [%d,%d] does not match default values [2,2]; assuming subsampling inside JPEG data is correct",sp->subsampling_hor,sp->subsampling_ver);
			else
				TIFFWarningExt(tif->tif_clientdata,module,"Subsampling inside JPEG data [%d,%d] does not match subsampling tag values [%d,%d]; assuming subsampling inside JPEG data is correct",sp->subsampling_hor,sp->subsampling_ver,mh,mv);
		}
		if (sp->subsampling_force_desubsampling_inside_decompression!=0)
		{
			if (sp->subsampling_tag==0)
				TIFFWarningExt(tif->tif_clientdata,module,"Subsampling tag is not set, yet subsampling inside JPEG data does not match default values [2,2] (nor any other values allowed in TIFF); assuming subsampling inside JPEG data is correct and desubsampling inside JPEG decompression");
			else
				TIFFWarningExt(tif->tif_clientdata,module,"Subsampling inside JPEG data does not match subsampling tag values [%d,%d] (nor any other values allowed in TIFF); assuming subsampling inside JPEG data is correct and desubsampling inside JPEG decompression",mh,mv);
		}
		if (sp->subsampling_force_desubsampling_inside_decompression==0)
		{
			if (sp->subsampling_hor<sp->subsampling_ver)
				TIFFWarningExt(tif->tif_clientdata,module,"Subsampling values [%d,%d] are not allowed in TIFF",sp->subsampling_hor,sp->subsampling_ver);
		}
	}
	sp->subsamplingcorrect_done=1;
}

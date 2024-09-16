OJPEGCleanup(TIFF* tif)
{
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	if (sp!=0)
	{
		tif->tif_tagmethods.vgetfield=sp->vgetparent;
		tif->tif_tagmethods.vsetfield=sp->vsetparent;
		tif->tif_tagmethods.printdir=sp->printdir;
		if (sp->qtable[0]!=0)
			_TIFFfree(sp->qtable[0]);
		if (sp->qtable[1]!=0)
			_TIFFfree(sp->qtable[1]);
		if (sp->qtable[2]!=0)
			_TIFFfree(sp->qtable[2]);
		if (sp->qtable[3]!=0)
			_TIFFfree(sp->qtable[3]);
		if (sp->dctable[0]!=0)
			_TIFFfree(sp->dctable[0]);
		if (sp->dctable[1]!=0)
			_TIFFfree(sp->dctable[1]);
		if (sp->dctable[2]!=0)
			_TIFFfree(sp->dctable[2]);
		if (sp->dctable[3]!=0)
			_TIFFfree(sp->dctable[3]);
		if (sp->actable[0]!=0)
			_TIFFfree(sp->actable[0]);
		if (sp->actable[1]!=0)
			_TIFFfree(sp->actable[1]);
		if (sp->actable[2]!=0)
			_TIFFfree(sp->actable[2]);
		if (sp->actable[3]!=0)
			_TIFFfree(sp->actable[3]);
		if (sp->libjpeg_session_active!=0)
			OJPEGLibjpegSessionAbort(tif);
		if (sp->subsampling_convert_ycbcrbuf!=0)
			_TIFFfree(sp->subsampling_convert_ycbcrbuf);
		if (sp->subsampling_convert_ycbcrimage!=0)
			_TIFFfree(sp->subsampling_convert_ycbcrimage);
		if (sp->skip_buffer!=0)
			_TIFFfree(sp->skip_buffer);
		_TIFFfree(sp);
		tif->tif_data=NULL;
		_TIFFSetDefaultCompressionState(tif);
	}
}

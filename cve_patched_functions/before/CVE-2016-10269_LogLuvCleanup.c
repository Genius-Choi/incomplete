LogLuvCleanup(TIFF* tif)
{
	LogLuvState* sp = (LogLuvState *)tif->tif_data;

	assert(sp != 0);

	tif->tif_tagmethods.vgetfield = sp->vgetparent;
	tif->tif_tagmethods.vsetfield = sp->vsetparent;

	if (sp->tbuf)
		_TIFFfree(sp->tbuf);
	_TIFFfree(sp);
	tif->tif_data = NULL;

	_TIFFSetDefaultCompressionState(tif);
}

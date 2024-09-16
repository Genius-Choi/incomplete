OJPEGSetupEncode(TIFF* tif)
{
	static const char module[]="OJPEGSetupEncode";
	TIFFErrorExt(tif->tif_clientdata,module,"OJPEG encoding not supported; use new-style JPEG compression instead");
	return(0);
}

OJPEGPostEncode(TIFF* tif)
{
	static const char module[]="OJPEGPostEncode";
	TIFFErrorExt(tif->tif_clientdata,module,"OJPEG encoding not supported; use new-style JPEG compression instead");
	return(0);
}

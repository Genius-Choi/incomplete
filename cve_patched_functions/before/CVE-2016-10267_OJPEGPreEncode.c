OJPEGPreEncode(TIFF* tif, uint16 s)
{
	static const char module[]="OJPEGPreEncode";
	(void)s;
	TIFFErrorExt(tif->tif_clientdata,module,"OJPEG encoding not supported; use new-style JPEG compression instead");
	return(0);
}

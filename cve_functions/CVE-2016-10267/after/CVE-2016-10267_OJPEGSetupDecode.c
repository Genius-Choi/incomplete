OJPEGSetupDecode(TIFF* tif)
{
	static const char module[]="OJPEGSetupDecode";
	TIFFWarningExt(tif->tif_clientdata,module,"Depreciated and troublesome old-style JPEG compression mode, please convert to new-style JPEG compression and notify vendor of writing software");
	return(1);
}

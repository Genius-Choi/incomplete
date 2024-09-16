OJPEGLibjpegJpegSourceMgrResyncToRestart(jpeg_decompress_struct* cinfo, int desired)
{
	TIFF* tif=(TIFF*)cinfo->client_data;
	(void)desired;
	TIFFErrorExt(tif->tif_clientdata,"LibJpeg","Unexpected error");
	jpeg_encap_unwind(tif);
	return(0);
}

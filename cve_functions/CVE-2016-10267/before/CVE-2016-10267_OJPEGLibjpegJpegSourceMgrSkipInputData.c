OJPEGLibjpegJpegSourceMgrSkipInputData(jpeg_decompress_struct* cinfo, long num_bytes)
{
	TIFF* tif=(TIFF*)cinfo->client_data;
	(void)num_bytes;
	TIFFErrorExt(tif->tif_clientdata,"LibJpeg","Unexpected error");
	jpeg_encap_unwind(tif);
}

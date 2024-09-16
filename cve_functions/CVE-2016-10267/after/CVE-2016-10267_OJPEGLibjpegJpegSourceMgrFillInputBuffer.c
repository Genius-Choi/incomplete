OJPEGLibjpegJpegSourceMgrFillInputBuffer(jpeg_decompress_struct* cinfo)
{
	TIFF* tif=(TIFF*)cinfo->client_data;
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	void* mem=0;
	uint32 len=0U;
	if (OJPEGWriteStream(tif,&mem,&len)==0)
	{
		TIFFErrorExt(tif->tif_clientdata,"LibJpeg","Premature end of JPEG data");
		jpeg_encap_unwind(tif);
	}
	sp->libjpeg_jpeg_source_mgr.bytes_in_buffer=len;
	sp->libjpeg_jpeg_source_mgr.next_input_byte=mem;
	return(1);
}

OJPEGLibjpegSessionAbort(TIFF* tif)
{
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	assert(sp->libjpeg_session_active!=0);
	jpeg_destroy((jpeg_common_struct*)(&(sp->libjpeg_jpeg_decompress_struct)));
	sp->libjpeg_session_active=0;
}

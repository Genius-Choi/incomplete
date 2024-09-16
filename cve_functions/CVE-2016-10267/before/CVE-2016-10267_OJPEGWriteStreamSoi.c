OJPEGWriteStreamSoi(TIFF* tif, void** mem, uint32* len)
{
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	assert(OJPEG_BUFFER>=2);
	sp->out_buffer[0]=255;
	sp->out_buffer[1]=JPEG_MARKER_SOI;
	*len=2;
	*mem=(void*)sp->out_buffer;
	sp->out_state++;
}

jpeg_encap_unwind(TIFF* tif)
{
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	LONGJMP(sp->exit_jmpbuf,1);
}

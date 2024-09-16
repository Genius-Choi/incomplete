jpeg_create_decompress_encap(OJPEGState* sp, jpeg_decompress_struct* cinfo)
{
	if( SETJMP(sp->exit_jmpbuf) )
		return 0;
	else {
		jpeg_create_decompress(cinfo);
		return 1;
	}
}

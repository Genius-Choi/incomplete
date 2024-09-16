jpeg_read_header_encap(OJPEGState* sp, jpeg_decompress_struct* cinfo, uint8 require_image)
{
	if( SETJMP(sp->exit_jmpbuf) )
		return 0;
	else {
		jpeg_read_header(cinfo,require_image);
		return 1;
	}
}

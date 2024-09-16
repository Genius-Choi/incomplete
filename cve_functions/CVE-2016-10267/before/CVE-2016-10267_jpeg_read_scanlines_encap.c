jpeg_read_scanlines_encap(OJPEGState* sp, jpeg_decompress_struct* cinfo, void* scanlines, uint32 max_lines)
{
	if( SETJMP(sp->exit_jmpbuf) )
		return 0;
	else {
		jpeg_read_scanlines(cinfo,scanlines,max_lines);
		return 1;
	}
}

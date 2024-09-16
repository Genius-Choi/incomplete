jpeg_read_raw_data_encap(OJPEGState* sp, jpeg_decompress_struct* cinfo, void* data, uint32 max_lines)
{
	if( SETJMP(sp->exit_jmpbuf) )
		return 0;
	else {
		jpeg_read_raw_data(cinfo,data,max_lines);
		return 1;
	}
}

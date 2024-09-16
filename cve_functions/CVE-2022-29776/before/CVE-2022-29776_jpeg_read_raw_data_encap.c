jpeg_read_raw_data_encap(OJPEGState* sp, jpeg_decompress_struct* cinfo, void* data, uint32 max_lines)
{
	return(SETJMP(sp->exit_jmpbuf)?0:(jpeg_read_raw_data(cinfo,data,max_lines),1));
}

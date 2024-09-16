safeboolean empty_output_buffer (j_compress_ptr cinfo)
{
	my_dest_ptr dest = (my_dest_ptr) cinfo->dest;

	if (gdPutBuf (dest->buffer, OUTPUT_BUF_SIZE, dest->outfile) != (size_t) OUTPUT_BUF_SIZE) {
		ERREXIT (cinfo, JERR_FILE_WRITE);
	}

	dest->pub.next_output_byte = dest->buffer;
	dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;

	return TRUE;
}

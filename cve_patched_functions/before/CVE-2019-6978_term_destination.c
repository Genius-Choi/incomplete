void term_destination (j_compress_ptr cinfo)
{
	my_dest_ptr dest = (my_dest_ptr) cinfo->dest;
	size_t datacount = OUTPUT_BUF_SIZE - dest->pub.free_in_buffer;

	/* Write any data remaining in the buffer */
	if (datacount > 0 && ((size_t)gdPutBuf (dest->buffer, datacount, dest->outfile) != datacount)) {
		ERREXIT (cinfo, JERR_FILE_WRITE);
	}
}

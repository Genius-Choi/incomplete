read_consume(struct archive_read *a)
{
	struct _7zip *zip = (struct _7zip *)a->format->data;

	if (zip->pack_stream_bytes_unconsumed) {
		__archive_read_consume(a, zip->pack_stream_bytes_unconsumed);
		zip->stream_offset += zip->pack_stream_bytes_unconsumed;
		zip->pack_stream_bytes_unconsumed = 0;
	}
}

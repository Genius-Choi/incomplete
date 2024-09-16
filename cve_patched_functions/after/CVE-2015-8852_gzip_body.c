gzip_body(const struct http *hp, const char *txt, char **body, int *bodylen)
{
	int l, i;
	z_stream vz;

	memset(&vz, 0, sizeof vz);

	l = strlen(txt);
	*body = calloc(l + OVERHEAD, 1);
	AN(*body);

	vz.next_in = TRUST_ME(txt);
	vz.avail_in = l;

	vz.next_out = TRUST_ME(*body);
	vz.avail_out = l + OVERHEAD;

	assert(Z_OK == deflateInit2(&vz,
	    hp->gziplevel, Z_DEFLATED, 31, 9, Z_DEFAULT_STRATEGY));
	assert(Z_STREAM_END == deflate(&vz, Z_FINISH));
	i = vz.stop_bit & 7;
	if (hp->gzipresidual >= 0 && hp->gzipresidual != i)
		vtc_log(hp->vl, hp->fatal,
		    "Wrong gzip residual got %d wanted %d",
		    i, hp->gzipresidual);
	*bodylen = vz.total_out;
	vtc_log(hp->vl, 4, "startbit = %ju %ju/%ju",
	    (uintmax_t)vz.start_bit,
	    (uintmax_t)vz.start_bit >> 3, (uintmax_t)vz.start_bit & 7);
	vtc_log(hp->vl, 4, "lastbit = %ju %ju/%ju",
	    (uintmax_t)vz.last_bit,
	    (uintmax_t)vz.last_bit >> 3, (uintmax_t)vz.last_bit & 7);
	vtc_log(hp->vl, 4, "stopbit = %ju %ju/%ju",
	    (uintmax_t)vz.stop_bit,
	    (uintmax_t)vz.stop_bit >> 3, (uintmax_t)vz.stop_bit & 7);
	assert(Z_OK == deflateEnd(&vz));
}

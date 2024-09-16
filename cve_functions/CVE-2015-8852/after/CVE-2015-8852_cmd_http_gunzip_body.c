cmd_http_gunzip_body(CMD_ARGS)
{
	int i;
	z_stream vz;
	struct http *hp;
	char *p;
	unsigned l;

	(void)cmd;
	(void)vl;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	ONLY_CLIENT(hp, av);

	memset(&vz, 0, sizeof vz);

	if (hp->body[0] != (char)0x1f || hp->body[1] != (char)0x8b)
		vtc_log(hp->vl, hp->fatal,
		    "Gunzip error: Body lacks gzip magics");
	vz.next_in = TRUST_ME(hp->body);
	vz.avail_in = hp->bodyl;

	l = hp->bodyl * 10;
	p = calloc(l, 1);
	AN(p);

	vz.next_out = TRUST_ME(p);
	vz.avail_out = l;

	assert(Z_OK == inflateInit2(&vz, 31));
	i = inflate(&vz, Z_FINISH);
	hp->bodyl = vz.total_out;
	memcpy(hp->body, p, hp->bodyl);
	free(p);
	vtc_log(hp->vl, 3, "new bodylen %u", hp->bodyl);
	vtc_dump(hp->vl, 4, "body", hp->body, hp->bodyl);
	bprintf(hp->bodylen, "%u", hp->bodyl);
	vtc_log(hp->vl, 4, "startbit = %ju %ju/%ju",
	    (uintmax_t)vz.start_bit,
	    (uintmax_t)vz.start_bit >> 3, (uintmax_t)vz.start_bit & 7);
	vtc_log(hp->vl, 4, "lastbit = %ju %ju/%ju",
	    (uintmax_t)vz.last_bit,
	    (uintmax_t)vz.last_bit >> 3, (uintmax_t)vz.last_bit & 7);
	vtc_log(hp->vl, 4, "stopbit = %ju %ju/%ju",
	    (uintmax_t)vz.stop_bit,
	    (uintmax_t)vz.stop_bit >> 3, (uintmax_t)vz.stop_bit & 7);
	if (i != Z_STREAM_END)
		vtc_log(hp->vl, hp->fatal,
		    "Gunzip error = %d (%s) in:%jd out:%jd",
		    i, vz.msg, (intmax_t)vz.total_in, (intmax_t)vz.total_out);
	assert(Z_OK == inflateEnd(&vz));
}

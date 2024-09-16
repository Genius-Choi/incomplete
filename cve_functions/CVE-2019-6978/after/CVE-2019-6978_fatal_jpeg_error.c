static void fatal_jpeg_error (j_common_ptr cinfo)
{
	jmpbuf_wrapper *jmpbufw;
	char buffer[JMSG_LENGTH_MAX];

	(*cinfo->err->format_message)(cinfo, buffer);
	gd_error_ex(GD_WARNING, "gd-jpeg: JPEG library reports unrecoverable error: %s", buffer);

	jmpbufw = (jmpbuf_wrapper *) cinfo->client_data;
	jpeg_destroy (cinfo);

	if (jmpbufw != 0) {
		longjmp (jmpbufw->jmpbuf, 1);
		gd_error_ex(GD_ERROR, "gd-jpeg: EXTREMELY fatal error: longjmp returned control; terminating");
	} else {
		gd_error_ex(GD_ERROR, "gd-jpeg: EXTREMELY fatal error: jmpbuf unrecoverable; terminating");
	}

	exit (99);
}

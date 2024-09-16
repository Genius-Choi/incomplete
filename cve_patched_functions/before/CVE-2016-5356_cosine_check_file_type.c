static gboolean cosine_check_file_type(wtap *wth, int *err, gchar **err_info)
{
	char	buf[COSINE_LINE_LENGTH];
	gsize	reclen;
	guint	line;

	buf[COSINE_LINE_LENGTH-1] = '\0';

	for (line = 0; line < COSINE_HEADER_LINES_TO_CHECK; line++) {
		if (file_gets(buf, COSINE_LINE_LENGTH, wth->fh) == NULL) {
			/* EOF or error. */
			*err = file_error(wth->fh, err_info);
			return FALSE;
		}

		reclen = strlen(buf);
		if (reclen < strlen(COSINE_HDR_MAGIC_STR1) ||
			reclen < strlen(COSINE_HDR_MAGIC_STR2)) {
			continue;
		}

		if (strstr(buf, COSINE_HDR_MAGIC_STR1) ||
		    strstr(buf, COSINE_HDR_MAGIC_STR2)) {
			return TRUE;
		}
	}
	*err = 0;
	return FALSE;
}

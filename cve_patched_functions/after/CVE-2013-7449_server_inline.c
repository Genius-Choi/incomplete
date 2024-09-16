server_inline (server *serv, char *line, int len)
{
	char *utf_line_allocated = NULL;

	/* Checks whether we're set to use UTF-8 charset */
	if (serv->using_irc ||				/* 1. using CP1252/UTF-8 Hybrid */
		(serv->encoding == NULL && prefs.utf8_locale) || /* OR 2. using system default->UTF-8 */
	    (serv->encoding != NULL &&				/* OR 3. explicitly set to UTF-8 */
		 (g_ascii_strcasecmp (serv->encoding, "UTF8") == 0 ||
		  g_ascii_strcasecmp (serv->encoding, "UTF-8") == 0)))
	{
		/* The user has the UTF-8 charset set, either via /charset
		command or from his UTF-8 locale. Thus, we first try the
		UTF-8 charset, and if we fail to convert, we assume
		it to be ISO-8859-1 (see text_validate). */

		utf_line_allocated = text_validate (&line, &len);

	} else
	{
		/* Since the user has an explicit charset set, either
		via /charset command or from his non-UTF8 locale,
		we don't fallback to ISO-8859-1 and instead try to remove
		errnoeous octets till the string is convertable in the
		said charset. */

		const char *encoding = NULL;

		if (serv->encoding != NULL)
			encoding = serv->encoding;
		else
			g_get_charset (&encoding);

		if (encoding != NULL)
		{
			char *conv_line; /* holds a copy of the original string */
			int conv_len; /* tells g_convert how much of line to convert */
			gsize utf_len;
			gsize read_len;
			GError *err;
			gboolean retry;

			conv_line = g_malloc (len + 1);
			memcpy (conv_line, line, len);
			conv_line[len] = 0;
			conv_len = len;

			/* if CP1255, convert it with the NUL terminator.
				Works around SF bug #1122089 */
			if (serv->using_cp1255)
				conv_len++;

			do
			{
				err = NULL;
				retry = FALSE;
				utf_line_allocated = g_convert_with_fallback (conv_line, conv_len, "UTF-8", encoding, "?", &read_len, &utf_len, &err);
				if (err != NULL)
				{
					if (err->code == G_CONVERT_ERROR_ILLEGAL_SEQUENCE && conv_len > (read_len + 1))
					{
						/* Make our best bet by removing the erroneous char.
						   This will work for casual 8-bit strings with non-standard chars. */
						memmove (conv_line + read_len, conv_line + read_len + 1, conv_len - read_len -1);
						conv_len--;
						retry = TRUE;
					}
					g_error_free (err);
				}
			} while (retry);

			g_free (conv_line);

			/* If any conversion has occured at all. Conversion might fail
			due to errors other than invalid sequences, e.g. unknown charset. */
			if (utf_line_allocated != NULL)
			{
				line = utf_line_allocated;
				len = utf_len;
				if (serv->using_cp1255 && len > 0)
					len--;
			}
			else
			{
				/* If all fails, treat as UTF-8 with fallback to ISO-8859-1. */
				utf_line_allocated = text_validate (&line, &len);
			}
		}
	}

	fe_add_rawlog (serv, line, len, FALSE);

	/* let proto-irc.c handle it */
	serv->p_inline (serv, line, len);

	if (utf_line_allocated != NULL) /* only if a special copy was allocated */
		g_free (utf_line_allocated);
}

expat_read_toc(struct archive_read *a)
{
	struct xar *xar;
	XML_Parser parser;
	struct expat_userData ud;

	ud.state = ARCHIVE_OK;
	ud.archive = a;

	xar = (struct xar *)(a->format->data);

	/* Initialize XML Parser library. */
	parser = XML_ParserCreate(NULL);
	if (parser == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Couldn't allocate memory for xml parser");
		return (ARCHIVE_FATAL);
	}
	XML_SetUserData(parser, &ud);
	XML_SetElementHandler(parser, expat_start_cb, expat_end_cb);
	XML_SetCharacterDataHandler(parser, expat_data_cb);
	xar->xmlsts = INIT;

	while (xar->toc_remaining && ud.state == ARCHIVE_OK) {
		enum XML_Status xr;
		const void *d;
		size_t outbytes;
		size_t used;
		int r;

		d = NULL;
		r = rd_contents(a, &d, &outbytes, &used, xar->toc_remaining);
		if (r != ARCHIVE_OK)
			return (r);
		xar->toc_remaining -= used;
		xar->offset += used;
		xar->toc_total += outbytes;
		PRINT_TOC(d, outbytes);

		xr = XML_Parse(parser, d, outbytes, xar->toc_remaining == 0);
		__archive_read_consume(a, used);
		if (xr == XML_STATUS_ERROR) {
			XML_ParserFree(parser);
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "XML Parsing failed");
			return (ARCHIVE_FATAL);
		}
	}
	XML_ParserFree(parser);
	return (ud.state);
}

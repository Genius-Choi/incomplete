sf_flac_meta_get_vorbiscomments (SF_PRIVATE *psf, const FLAC__StreamMetadata *metadata)
{	static FLAC_TAG tags [] =
	{ 	{ "title", SF_STR_TITLE },
		{ "copyright", SF_STR_COPYRIGHT },
		{ "software", SF_STR_SOFTWARE },
		{ "artist", SF_STR_ARTIST },
		{ "comment", SF_STR_COMMENT },
		{ "date", SF_STR_DATE },
		{ "album", SF_STR_ALBUM },
		{ "license", SF_STR_LICENSE },
		{ "tracknumber", SF_STR_TRACKNUMBER },
		{ "genre", SF_STR_GENRE }
		} ;

	const char *value, *cptr ;
	int k, tag_num ;

	for (k = 0 ; k < ARRAY_LEN (tags) ; k++)
	{	tag_num = FLAC__metadata_object_vorbiscomment_find_entry_from (metadata, 0, tags [k].tag) ;

		if (tag_num < 0)
			continue ;

		value = (const char*) metadata->data.vorbis_comment.comments [tag_num].entry ;
		if ((cptr = strchr (value, '=')) != NULL)
			value = cptr + 1 ;

		psf_log_printf (psf, "  %-12s : %s\n", tags [k].tag, value) ;
		psf_store_string (psf, tags [k].type, value) ;
		} ;

	return ;
} /* sf_flac_meta_get_vorbiscomments */

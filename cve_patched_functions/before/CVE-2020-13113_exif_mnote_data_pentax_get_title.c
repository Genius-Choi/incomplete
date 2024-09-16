exif_mnote_data_pentax_get_title (ExifMnoteData *d, unsigned int n)
{
	ExifMnoteDataPentax *note = (ExifMnoteDataPentax *) d;

	if (!note) return NULL;
	if (note->count <= n) return NULL;
	return mnote_pentax_tag_get_title (note->entries[n].tag);
}

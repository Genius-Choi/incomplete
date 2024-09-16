exif_mnote_data_canon_get_tags (ExifMnoteDataCanon *dc, unsigned int n,
		unsigned int *m, unsigned int *s)
{
	unsigned int from = 0, to;

	if (!dc || !m) return;
	for (*m = 0; *m < dc->count; (*m)++) {
		to = from + mnote_canon_entry_count_values (&dc->entries[*m]);
		if (to > n) {
			if (s) *s = n - from;
			break;
		}
		from = to;
	}
}

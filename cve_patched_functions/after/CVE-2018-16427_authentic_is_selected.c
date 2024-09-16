authentic_is_selected(struct sc_card *card, const struct sc_path *path, struct sc_file **file_out)
{
	if (!path->len)   {
		if (file_out && card->cache.valid && card->cache.current_df)
			sc_file_dup(file_out, card->cache.current_df);
		return SC_SUCCESS;
	}
	else if (path->len == 2 && card->cache.valid && card->cache.current_ef)   {
		if (!memcmp(card->cache.current_ef->path.value, path->value, 2))   {
			if (file_out)
				sc_file_dup(file_out, card->cache.current_ef);
			return SC_SUCCESS;
		}
	}

	return SC_ERROR_FILE_NOT_FOUND;
}

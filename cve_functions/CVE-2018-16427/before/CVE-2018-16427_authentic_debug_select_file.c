authentic_debug_select_file(struct sc_card *card, const struct sc_path *path)
{
	struct sc_context *ctx = card->ctx;
	struct sc_card_cache *cache = &card->cache;

	if (path)
		sc_log(ctx, "try to select path(type:%i) %s",
				path->type, sc_print_path(path));

	if (!cache->valid)
		return;

	if (cache->current_df)
		sc_log(ctx, "current_df(type=%i) %s",
				cache->current_df->path.type, sc_print_path(&cache->current_df->path));
	else
		sc_log(ctx, "current_df empty");

	if (cache->current_ef)
		sc_log(ctx, "current_ef(type=%i) %s",
				cache->current_ef->path.type, sc_print_path(&cache->current_ef->path));
	else
		sc_log(ctx, "current_ef empty");
}

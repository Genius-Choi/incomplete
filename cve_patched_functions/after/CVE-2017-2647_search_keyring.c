static int search_keyring(struct key *keyring, struct keyring_search_context *ctx)
{
	if (ctx->match_data.lookup_type == KEYRING_SEARCH_LOOKUP_DIRECT) {
		const void *object;

		object = assoc_array_find(&keyring->keys,
					  &keyring_assoc_array_ops,
					  &ctx->index_key);
		return object ? ctx->iterator(object, ctx) : 0;
	}
	return assoc_array_iterate(&keyring->keys, ctx->iterator, ctx);
}

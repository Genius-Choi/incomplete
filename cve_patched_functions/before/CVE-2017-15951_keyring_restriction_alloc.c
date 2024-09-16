static struct key_restriction *keyring_restriction_alloc(
	key_restrict_link_func_t check)
{
	struct key_restriction *keyres =
		kzalloc(sizeof(struct key_restriction), GFP_KERNEL);

	if (!keyres)
		return ERR_PTR(-ENOMEM);

	keyres->check = check;

	return keyres;
}

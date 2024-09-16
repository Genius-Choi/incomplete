static int __key_link_check_restriction(struct key *keyring, struct key *key)
{
	if (!keyring->restrict_link || !keyring->restrict_link->check)
		return 0;
	return keyring->restrict_link->check(keyring, key->type, &key->payload,
					     keyring->restrict_link->key);
}

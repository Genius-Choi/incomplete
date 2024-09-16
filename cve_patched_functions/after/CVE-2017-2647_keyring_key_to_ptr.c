static inline void *keyring_key_to_ptr(struct key *key)
{
	if (key->type == &key_type_keyring)
		return (void *)((unsigned long)key | KEYRING_PTR_SUBTYPE);
	return key;
}

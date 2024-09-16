static unsigned long keyring_get_object_key_chunk(const void *object, int level)
{
	const struct key *key = keyring_ptr_to_key(object);
	return keyring_get_key_chunk(&key->index_key, level);
}

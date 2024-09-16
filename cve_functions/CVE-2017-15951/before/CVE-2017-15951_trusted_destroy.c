static void trusted_destroy(struct key *key)
{
	kzfree(key->payload.data[0]);
}

static void request_key_auth_destroy(struct key *key)
{
	struct request_key_auth *rka = key->payload.data[0];

	kenter("{%d}", key->serial);

	free_request_key_auth(rka);
}

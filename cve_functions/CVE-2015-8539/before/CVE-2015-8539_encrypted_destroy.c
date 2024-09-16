static void encrypted_destroy(struct key *key)
{
	struct encrypted_key_payload *epayload = key->payload.data[0];

	if (!epayload)
		return;

	memset(epayload->decrypted_data, 0, epayload->decrypted_datalen);
	kfree(key->payload.data[0]);
}

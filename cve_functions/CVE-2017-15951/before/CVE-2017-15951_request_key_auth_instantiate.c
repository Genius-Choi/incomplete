static int request_key_auth_instantiate(struct key *key,
					struct key_preparsed_payload *prep)
{
	key->payload.data[0] = (struct request_key_auth *)prep->data;
	return 0;
}

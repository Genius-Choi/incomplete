static void free_request_key_auth(struct request_key_auth *rka)
{
	if (!rka)
		return;
	key_put(rka->target_key);
	key_put(rka->dest_keyring);
	if (rka->cred)
		put_cred(rka->cred);
	kfree(rka->callout_info);
	kfree(rka);
}

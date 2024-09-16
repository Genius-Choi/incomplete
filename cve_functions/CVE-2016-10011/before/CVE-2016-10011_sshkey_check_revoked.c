sshkey_check_revoked(struct sshkey *key, const char *revoked_keys_file)
{
	int r;

	r = ssh_krl_file_contains_key(revoked_keys_file, key);
	/* If this was not a KRL to begin with then continue below */
	if (r != SSH_ERR_KRL_BAD_MAGIC)
		return r;

	/*
	 * If the file is not a KRL or we can't handle KRLs then attempt to
	 * parse the file as a flat list of keys.
	 */
	switch ((r = sshkey_in_file(key, revoked_keys_file, 0, 1))) {
	case 0:
		/* Key found => revoked */
		return SSH_ERR_KEY_REVOKED;
	case SSH_ERR_KEY_NOT_FOUND:
		/* Key not found => not revoked */
		return 0;
	default:
		/* Some other error occurred */
		return r;
	}
}

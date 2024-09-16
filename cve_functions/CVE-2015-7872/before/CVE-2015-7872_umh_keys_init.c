static int umh_keys_init(struct subprocess_info *info, struct cred *cred)
{
	struct key *keyring = info->data;

	return install_session_keyring_to_cred(cred, keyring);
}

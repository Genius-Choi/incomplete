int keyring_restrict(key_ref_t keyring_ref, const char *type,
		     const char *restriction)
{
	struct key *keyring;
	struct key_type *restrict_type = NULL;
	struct key_restriction *restrict_link;
	int ret = 0;

	keyring = key_ref_to_ptr(keyring_ref);
	key_check(keyring);

	if (keyring->type != &key_type_keyring)
		return -ENOTDIR;

	if (!type) {
		restrict_link = keyring_restriction_alloc(restrict_link_reject);
	} else {
		restrict_type = key_type_lookup(type);

		if (IS_ERR(restrict_type))
			return PTR_ERR(restrict_type);

		if (!restrict_type->lookup_restriction) {
			ret = -ENOENT;
			goto error;
		}

		restrict_link = restrict_type->lookup_restriction(restriction);
	}

	if (IS_ERR(restrict_link)) {
		ret = PTR_ERR(restrict_link);
		goto error;
	}

	down_write(&keyring->sem);
	down_write(&keyring_serialise_restrict_sem);

	if (keyring->restrict_link)
		ret = -EEXIST;
	else if (keyring_detect_restriction_cycle(keyring, restrict_link))
		ret = -EDEADLK;
	else
		keyring->restrict_link = restrict_link;

	up_write(&keyring_serialise_restrict_sem);
	up_write(&keyring->sem);

	if (ret < 0) {
		key_put(restrict_link->key);
		kfree(restrict_link);
	}

error:
	if (restrict_type)
		key_type_put(restrict_type);

	return ret;
}

static bool keyring_detect_restriction_cycle(const struct key *dest_keyring,
					     struct key_restriction *keyres)
{
	while (keyres && keyres->key &&
	       keyres->key->type == &key_type_keyring) {
		if (keyres->key == dest_keyring)
			return true;

		keyres = keyres->key->restrict_link;
	}

	return false;
}

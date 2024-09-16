static void keyring_destroy(struct key *keyring)
{
	if (keyring->description) {
		write_lock(&keyring_name_lock);

		if (keyring->type_data.link.next != NULL &&
		    !list_empty(&keyring->type_data.link))
			list_del(&keyring->type_data.link);

		write_unlock(&keyring_name_lock);
	}

	assoc_array_destroy(&keyring->keys, &keyring_assoc_array_ops);
}

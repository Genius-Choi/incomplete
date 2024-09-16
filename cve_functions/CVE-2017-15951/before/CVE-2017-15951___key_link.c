void __key_link(struct key *key, struct assoc_array_edit **_edit)
{
	__key_get(key);
	assoc_array_insert_set_object(*_edit, keyring_key_to_ptr(key));
	assoc_array_apply_edit(*_edit);
	*_edit = NULL;
}

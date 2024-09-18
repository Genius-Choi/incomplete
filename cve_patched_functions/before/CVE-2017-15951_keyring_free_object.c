static void keyring_free_object(void *object)
{
	key_put(keyring_ptr_to_key(object));
}

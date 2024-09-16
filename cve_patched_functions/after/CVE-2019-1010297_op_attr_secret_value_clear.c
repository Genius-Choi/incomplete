static void op_attr_secret_value_clear(void *attr)
{
	struct tee_cryp_obj_secret *key = attr;

	key->key_size = 0;
	memset(key + 1, 0, key->alloc_size);
}

static TEE_Result op_attr_secret_value_to_user(void *attr,
			struct tee_ta_session *sess __unused,
			void *buffer, uint64_t *size)
{
	TEE_Result res;
	struct tee_cryp_obj_secret *key = attr;
	uint64_t s;
	uint64_t key_size;

	res = tee_svc_copy_from_user(&s, size, sizeof(s));
	if (res != TEE_SUCCESS)
		return res;

	key_size = key->key_size;
	res = tee_svc_copy_to_user(size, &key_size, sizeof(key_size));
	if (res != TEE_SUCCESS)
		return res;

	if (s < key->key_size || !buffer)
		return TEE_ERROR_SHORT_BUFFER;

	return tee_svc_copy_to_user(buffer, key + 1, key->key_size);
}

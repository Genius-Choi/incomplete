static long dns_resolver_read(const struct key *key,
			      char __user *buffer, size_t buflen)
{
	int err = PTR_ERR(key->payload.data[dns_key_error]);

	if (err)
		return err;

	return user_read(key, buffer, buflen);
}

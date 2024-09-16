int restrict_link_reject(struct key *keyring,
			 const struct key_type *type,
			 const union key_payload *payload,
			 struct key *restriction_key)
{
	return -EPERM;
}

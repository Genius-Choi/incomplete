static inline bool keyring_ptr_is_keyring(const struct assoc_array_ptr *x)
{
	return (unsigned long)x & KEYRING_PTR_SUBTYPE;
}

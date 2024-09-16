static inline int nlm_cookie_match(struct nlm_cookie *a, struct nlm_cookie *b)
{
	if (a->len != b->len)
		return 0;
	if (memcmp(a->data, b->data, a->len))
		return 0;
	return 1;
}

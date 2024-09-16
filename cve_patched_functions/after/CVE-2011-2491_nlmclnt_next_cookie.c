void nlmclnt_next_cookie(struct nlm_cookie *c)
{
	u32	cookie = atomic_inc_return(&nlm_cookie);

	memcpy(c->data, &cookie, 4);
	c->len=4;
}

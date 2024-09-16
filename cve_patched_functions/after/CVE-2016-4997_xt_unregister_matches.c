xt_unregister_matches(struct xt_match *match, unsigned int n)
{
	while (n-- > 0)
		xt_unregister_match(&match[n]);
}

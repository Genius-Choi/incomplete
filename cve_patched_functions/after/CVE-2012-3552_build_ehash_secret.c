void build_ehash_secret(void)
{
	u32 rnd;

	do {
		get_random_bytes(&rnd, sizeof(rnd));
	} while (rnd == 0);

	cmpxchg(&inet_ehash_secret, 0, rnd);
}

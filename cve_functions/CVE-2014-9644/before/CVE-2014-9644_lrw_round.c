static inline void lrw_round(struct sinfo *s, void *dst, const void *src)
{
	be128_xor(dst, &s->t, src);		/* PP <- T xor P */
	s->fn(s->tfm, dst, dst);		/* CC <- E(Key2,PP) */
	be128_xor(dst, dst, &s->t);		/* C <- T xor CC */
}

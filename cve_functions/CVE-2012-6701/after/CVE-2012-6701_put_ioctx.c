static inline void put_ioctx(struct kioctx *kioctx)
{
	BUG_ON(atomic_read(&kioctx->users) <= 0);
	if (unlikely(atomic_dec_and_test(&kioctx->users)))
		__put_ioctx(kioctx);
}

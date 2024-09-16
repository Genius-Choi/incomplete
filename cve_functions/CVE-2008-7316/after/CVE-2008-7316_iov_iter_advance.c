void iov_iter_advance(struct iov_iter *i, size_t bytes)
{
	BUG_ON(i->count < bytes);

	__iov_iter_advance_iov(i, bytes);
	i->count -= bytes;
}

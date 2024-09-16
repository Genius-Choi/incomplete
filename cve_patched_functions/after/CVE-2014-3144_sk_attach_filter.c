int sk_attach_filter(struct sock_fprog *fprog, struct sock *sk)
{
	struct sk_filter *fp, *old_fp;
	unsigned int fsize = sk_filter_proglen(fprog);
	unsigned int sk_fsize = sk_filter_size(fprog->len);
	int err;

	if (sock_flag(sk, SOCK_FILTER_LOCKED))
		return -EPERM;

	/* Make sure new filter is there and in the right amounts. */
	if (fprog->filter == NULL)
		return -EINVAL;

	fp = sock_kmalloc(sk, sk_fsize, GFP_KERNEL);
	if (!fp)
		return -ENOMEM;

	if (copy_from_user(fp->insns, fprog->filter, fsize)) {
		sock_kfree_s(sk, fp, sk_fsize);
		return -EFAULT;
	}

	atomic_set(&fp->refcnt, 1);
	fp->len = fprog->len;

	err = sk_store_orig_filter(fp, fprog);
	if (err) {
		sk_filter_uncharge(sk, fp);
		return -ENOMEM;
	}

	/* __sk_prepare_filter() already takes care of uncharging
	 * memory in case something goes wrong.
	 */
	fp = __sk_prepare_filter(fp, sk);
	if (IS_ERR(fp))
		return PTR_ERR(fp);

	old_fp = rcu_dereference_protected(sk->sk_filter,
					   sock_owned_by_user(sk));
	rcu_assign_pointer(sk->sk_filter, fp);

	if (old_fp)
		sk_filter_uncharge(sk, old_fp);

	return 0;
}

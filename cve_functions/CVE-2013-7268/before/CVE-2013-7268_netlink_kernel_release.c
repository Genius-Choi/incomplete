netlink_kernel_release(struct sock *sk)
{
	sk_release_kernel(sk);
}

static int vsock_stream_getsockopt(struct socket *sock,
				   int level, int optname,
				   char __user *optval,
				   int __user *optlen)
{
	int err;
	int len;
	struct sock *sk;
	struct vsock_sock *vsk;
	u64 val;

	if (level != AF_VSOCK)
		return -ENOPROTOOPT;

	err = get_user(len, optlen);
	if (err != 0)
		return err;

#define COPY_OUT(_v)                            \
	do {					\
		if (len < sizeof(_v))		\
			return -EINVAL;		\
						\
		len = sizeof(_v);		\
		if (copy_to_user(optval, &_v, len) != 0)	\
			return -EFAULT;				\
								\
	} while (0)

	err = 0;
	sk = sock->sk;
	vsk = vsock_sk(sk);

	switch (optname) {
	case SO_VM_SOCKETS_BUFFER_SIZE:
		val = transport->get_buffer_size(vsk);
		COPY_OUT(val);
		break;

	case SO_VM_SOCKETS_BUFFER_MAX_SIZE:
		val = transport->get_max_buffer_size(vsk);
		COPY_OUT(val);
		break;

	case SO_VM_SOCKETS_BUFFER_MIN_SIZE:
		val = transport->get_min_buffer_size(vsk);
		COPY_OUT(val);
		break;

	case SO_VM_SOCKETS_CONNECT_TIMEOUT: {
		struct timeval tv;
		tv.tv_sec = vsk->connect_timeout / HZ;
		tv.tv_usec =
		    (vsk->connect_timeout -
		     tv.tv_sec * HZ) * (1000000 / HZ);
		COPY_OUT(tv);
		break;
	}
	default:
		return -ENOPROTOOPT;
	}

	err = put_user(len, optlen);
	if (err != 0)
		return -EFAULT;

#undef COPY_OUT

	return 0;
}

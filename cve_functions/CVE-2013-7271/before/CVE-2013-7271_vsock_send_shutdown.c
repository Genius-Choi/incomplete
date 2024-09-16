static int vsock_send_shutdown(struct sock *sk, int mode)
{
	return transport->shutdown(vsock_sk(sk), mode);
}

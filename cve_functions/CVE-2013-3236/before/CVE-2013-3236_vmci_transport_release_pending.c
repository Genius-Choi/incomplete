static void vmci_transport_release_pending(struct sock *pending)
{
	sock_put(pending);
}

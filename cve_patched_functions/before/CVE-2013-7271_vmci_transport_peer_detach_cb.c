static void vmci_transport_peer_detach_cb(u32 sub_id,
					  const struct vmci_event_data *e_data,
					  void *client_data)
{
	struct sock *sk = client_data;
	const struct vmci_event_payload_qp *e_payload;
	struct vsock_sock *vsk;

	e_payload = vmci_event_data_const_payload(e_data);
	vsk = vsock_sk(sk);
	if (vmci_handle_is_invalid(e_payload->handle))
		return;

	/* Same rules for locking as for peer_attach_cb(). */
	local_bh_disable();
	bh_lock_sock(sk);

	/* XXX This is lame, we should provide a way to lookup sockets by
	 * qp_handle.
	 */
	if (vmci_handle_is_equal(vmci_trans(vsk)->qp_handle,
				 e_payload->handle))
		vmci_transport_handle_detach(sk);

	bh_unlock_sock(sk);
	local_bh_enable();
}

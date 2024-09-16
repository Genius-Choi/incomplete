static void vmci_transport_peer_attach_cb(u32 sub_id,
					  const struct vmci_event_data *e_data,
					  void *client_data)
{
	struct sock *sk = client_data;
	const struct vmci_event_payload_qp *e_payload;
	struct vsock_sock *vsk;

	e_payload = vmci_event_data_const_payload(e_data);

	vsk = vsock_sk(sk);

	/* We don't ask for delayed CBs when we subscribe to this event (we
	 * pass 0 as flags to vmci_event_subscribe()).  VMCI makes no
	 * guarantees in that case about what context we might be running in,
	 * so it could be BH or process, blockable or non-blockable.  So we
	 * need to account for all possible contexts here.
	 */
	local_bh_disable();
	bh_lock_sock(sk);

	/* XXX This is lame, we should provide a way to lookup sockets by
	 * qp_handle.
	 */
	if (vmci_handle_is_equal(vmci_trans(vsk)->qp_handle,
				 e_payload->handle)) {
		/* XXX This doesn't do anything, but in the future we may want
		 * to set a flag here to verify the attach really did occur and
		 * we weren't just sent a datagram claiming it was.
		 */
		goto out;
	}

out:
	bh_unlock_sock(sk);
	local_bh_enable();
}

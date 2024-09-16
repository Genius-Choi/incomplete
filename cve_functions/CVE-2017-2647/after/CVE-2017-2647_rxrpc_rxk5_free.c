static void rxrpc_rxk5_free(struct rxk5_key *rxk5)
{
	int loop;

	rxrpc_free_krb5_principal(&rxk5->client);
	rxrpc_free_krb5_principal(&rxk5->server);
	rxrpc_free_krb5_tagged(&rxk5->session);

	if (rxk5->addresses) {
		for (loop = rxk5->n_addresses - 1; loop >= 0; loop--)
			rxrpc_free_krb5_tagged(&rxk5->addresses[loop]);
		kfree(rxk5->addresses);
	}
	if (rxk5->authdata) {
		for (loop = rxk5->n_authdata - 1; loop >= 0; loop--)
			rxrpc_free_krb5_tagged(&rxk5->authdata[loop]);
		kfree(rxk5->authdata);
	}

	kfree(rxk5->ticket);
	kfree(rxk5->ticket2);
	kfree(rxk5);
}

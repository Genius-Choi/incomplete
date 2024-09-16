static int rxrpc_preparse_xdr_rxk5(struct key_preparsed_payload *prep,
				   size_t datalen,
				   const __be32 *xdr, unsigned int toklen)
{
	struct rxrpc_key_token *token, **pptoken;
	struct rxk5_key *rxk5;
	const __be32 *end_xdr = xdr + (toklen >> 2);
	int ret;

	_enter(",{%x,%x,%x,%x},%u",
	       ntohl(xdr[0]), ntohl(xdr[1]), ntohl(xdr[2]), ntohl(xdr[3]),
	       toklen);

	/* reserve some payload space for this subkey - the length of the token
	 * is a reasonable approximation */
	prep->quotalen = datalen + toklen;

	token = kzalloc(sizeof(*token), GFP_KERNEL);
	if (!token)
		return -ENOMEM;

	rxk5 = kzalloc(sizeof(*rxk5), GFP_KERNEL);
	if (!rxk5) {
		kfree(token);
		return -ENOMEM;
	}

	token->security_index = RXRPC_SECURITY_RXK5;
	token->k5 = rxk5;

	/* extract the principals */
	ret = rxrpc_krb5_decode_principal(&rxk5->client, &xdr, &toklen);
	if (ret < 0)
		goto error;
	ret = rxrpc_krb5_decode_principal(&rxk5->server, &xdr, &toklen);
	if (ret < 0)
		goto error;

	/* extract the session key and the encoding type (the tag field ->
	 * ENCTYPE_xxx) */
	ret = rxrpc_krb5_decode_tagged_data(&rxk5->session, AFSTOKEN_DATA_MAX,
					    &xdr, &toklen);
	if (ret < 0)
		goto error;

	if (toklen < 4 * 8 + 2 * 4)
		goto inval;
	rxk5->authtime	= be64_to_cpup((const __be64 *) xdr);
	xdr += 2;
	rxk5->starttime	= be64_to_cpup((const __be64 *) xdr);
	xdr += 2;
	rxk5->endtime	= be64_to_cpup((const __be64 *) xdr);
	xdr += 2;
	rxk5->renew_till = be64_to_cpup((const __be64 *) xdr);
	xdr += 2;
	rxk5->is_skey = ntohl(*xdr++);
	rxk5->flags = ntohl(*xdr++);
	toklen -= 4 * 8 + 2 * 4;

	_debug("times: a=%llx s=%llx e=%llx rt=%llx",
	       rxk5->authtime, rxk5->starttime, rxk5->endtime,
	       rxk5->renew_till);
	_debug("is_skey=%x flags=%x", rxk5->is_skey, rxk5->flags);

	/* extract the permitted client addresses */
	ret = rxrpc_krb5_decode_tagged_array(&rxk5->addresses,
					     &rxk5->n_addresses,
					     AFSTOKEN_K5_ADDRESSES_MAX,
					     AFSTOKEN_DATA_MAX,
					     &xdr, &toklen);
	if (ret < 0)
		goto error;

	ASSERTCMP((end_xdr - xdr) << 2, ==, toklen);

	/* extract the tickets */
	ret = rxrpc_krb5_decode_ticket(&rxk5->ticket, &rxk5->ticket_len,
				       &xdr, &toklen);
	if (ret < 0)
		goto error;
	ret = rxrpc_krb5_decode_ticket(&rxk5->ticket2, &rxk5->ticket2_len,
				       &xdr, &toklen);
	if (ret < 0)
		goto error;

	ASSERTCMP((end_xdr - xdr) << 2, ==, toklen);

	/* extract the typed auth data */
	ret = rxrpc_krb5_decode_tagged_array(&rxk5->authdata,
					     &rxk5->n_authdata,
					     AFSTOKEN_K5_AUTHDATA_MAX,
					     AFSTOKEN_BDATALN_MAX,
					     &xdr, &toklen);
	if (ret < 0)
		goto error;

	ASSERTCMP((end_xdr - xdr) << 2, ==, toklen);

	if (toklen != 0)
		goto inval;

	/* attach the payload */
	for (pptoken = (struct rxrpc_key_token **)&prep->payload[0];
	     *pptoken;
	     pptoken = &(*pptoken)->next)
		continue;
	*pptoken = token;
	if (token->kad->expiry < prep->expiry)
		prep->expiry = token->kad->expiry;

	_leave(" = 0");
	return 0;

inval:
	ret = -EINVAL;
error:
	rxrpc_rxk5_free(rxk5);
	kfree(token);
	_leave(" = %d", ret);
	return ret;
}

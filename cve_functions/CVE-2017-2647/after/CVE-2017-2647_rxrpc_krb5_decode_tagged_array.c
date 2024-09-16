static int rxrpc_krb5_decode_tagged_array(struct krb5_tagged_data **_td,
					  u8 *_n_elem,
					  u8 max_n_elem,
					  size_t max_elem_size,
					  const __be32 **_xdr,
					  unsigned int *_toklen)
{
	struct krb5_tagged_data *td;
	const __be32 *xdr = *_xdr;
	unsigned int toklen = *_toklen, n_elem, loop;
	int ret;

	/* there must be at least one count */
	if (toklen < 4)
		return -EINVAL;

	_enter(",,%u,%zu,{%x},%u",
	       max_n_elem, max_elem_size, ntohl(xdr[0]), toklen);

	n_elem = ntohl(*xdr++);
	toklen -= 4;
	if (n_elem < 0 || n_elem > max_n_elem)
		return -EINVAL;
	*_n_elem = n_elem;
	if (n_elem > 0) {
		if (toklen <= (n_elem + 1) * 4)
			return -EINVAL;

		_debug("n_elem %d", n_elem);

		td = kcalloc(n_elem, sizeof(struct krb5_tagged_data),
			     GFP_KERNEL);
		if (!td)
			return -ENOMEM;
		*_td = td;

		for (loop = 0; loop < n_elem; loop++) {
			ret = rxrpc_krb5_decode_tagged_data(&td[loop],
							    max_elem_size,
							    &xdr, &toklen);
			if (ret < 0)
				return ret;
		}
	}

	*_xdr = xdr;
	*_toklen = toklen;
	_leave(" = 0 [toklen=%u]", toklen);
	return 0;
}

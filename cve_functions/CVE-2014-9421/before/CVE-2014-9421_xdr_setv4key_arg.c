xdr_setv4key_arg(XDR *xdrs, setv4key_arg *objp)
{
	unsigned int n_keys = 1;

	if (!xdr_ui_4(xdrs, &objp->api_version)) {
		return (FALSE);
	}
	if (!xdr_krb5_principal(xdrs, &objp->princ)) {
		return (FALSE);
	}
	if (!xdr_array(xdrs, (caddr_t *) &objp->keyblock,
		       &n_keys, ~0,
		       sizeof(krb5_keyblock), xdr_krb5_keyblock)) {
		return (FALSE);
	}
	return (TRUE);
}

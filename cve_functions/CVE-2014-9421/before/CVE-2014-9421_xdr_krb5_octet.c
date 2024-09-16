xdr_krb5_octet(XDR *xdrs, krb5_octet *objp)
{
   if (!xdr_u_char(xdrs, objp))
	return (FALSE);
   return (TRUE);
}

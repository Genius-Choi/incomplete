xdr_kadm5_policy_ent_rec(XDR *xdrs, kadm5_policy_ent_rec *objp)
{
	return _xdr_kadm5_policy_ent_rec(xdrs, objp, KADM5_API_VERSION_4);
}

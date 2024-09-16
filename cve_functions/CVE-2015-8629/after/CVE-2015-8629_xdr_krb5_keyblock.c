xdr_krb5_keyblock(XDR *xdrs, krb5_keyblock *objp)
{
   /* XXX This only works because free_keyblock assumes ->contents
      is allocated by malloc() */

   if(!xdr_krb5_enctype(xdrs, &objp->enctype))
      return FALSE;
   if(!xdr_bytes(xdrs, (char **) &objp->contents, (unsigned int *)
		 &objp->length, ~0))
      return FALSE;
   return TRUE;
}

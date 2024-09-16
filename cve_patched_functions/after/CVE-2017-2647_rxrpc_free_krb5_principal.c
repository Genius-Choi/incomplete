static void rxrpc_free_krb5_principal(struct krb5_principal *princ)
{
	int loop;

	if (princ->name_parts) {
		for (loop = princ->n_name_parts - 1; loop >= 0; loop--)
			kfree(princ->name_parts[loop]);
		kfree(princ->name_parts);
	}
	kfree(princ->realm);
}

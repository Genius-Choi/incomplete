x509_verify_param_zero(X509_VERIFY_PARAM *param)
{
	X509_VERIFY_PARAM_ID *paramid;
	if (!param)
		return;
	param->name = NULL;
	param->purpose = 0;
	param->trust = 0;
	/*param->inh_flags = X509_VP_FLAG_DEFAULT;*/
	param->inh_flags = 0;
	param->flags = 0;
	param->depth = -1;
	if (param->policies) {
		sk_ASN1_OBJECT_pop_free(param->policies, ASN1_OBJECT_free);
		param->policies = NULL;
	}
	paramid = param->id;
	if (paramid->hosts) {
		string_stack_free(paramid->hosts);
		paramid->hosts = NULL;
	}
	free(paramid->peername);
	paramid->peername = NULL;
	free(paramid->email);
	paramid->email = NULL;
	paramid->emaillen = 0;
	free(paramid->ip);
	paramid->ip = NULL;
	paramid->iplen = 0;
}

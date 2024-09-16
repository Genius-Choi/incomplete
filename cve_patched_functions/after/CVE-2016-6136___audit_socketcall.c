int __audit_socketcall(int nargs, unsigned long *args)
{
	struct audit_context *context = current->audit_context;

	if (nargs <= 0 || nargs > AUDITSC_ARGS || !args)
		return -EINVAL;
	context->type = AUDIT_SOCKETCALL;
	context->socketcall.nargs = nargs;
	memcpy(context->socketcall.args, args, nargs * sizeof(unsigned long));
	return 0;
}

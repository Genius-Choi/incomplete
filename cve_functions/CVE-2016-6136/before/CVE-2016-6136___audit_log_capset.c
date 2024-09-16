void __audit_log_capset(const struct cred *new, const struct cred *old)
{
	struct audit_context *context = current->audit_context;
	context->capset.pid = task_pid_nr(current);
	context->capset.cap.effective   = new->cap_effective;
	context->capset.cap.inheritable = new->cap_effective;
	context->capset.cap.permitted   = new->cap_permitted;
	context->type = AUDIT_CAPSET;
}

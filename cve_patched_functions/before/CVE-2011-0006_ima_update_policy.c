void ima_update_policy(void)
{
	const char *op = "policy_update";
	const char *cause = "already exists";
	int result = 1;
	int audit_info = 0;

	if (ima_measure == &measure_default_rules) {
		ima_measure = &measure_policy_rules;
		cause = "complete";
		result = 0;
	}
	integrity_audit_msg(AUDIT_INTEGRITY_STATUS, NULL,
			    NULL, op, cause, result, audit_info);
}

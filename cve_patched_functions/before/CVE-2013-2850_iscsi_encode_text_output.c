int iscsi_encode_text_output(
	u8 phase,
	u8 sender,
	char *textbuf,
	u32 *length,
	struct iscsi_param_list *param_list)
{
	char *output_buf = NULL;
	struct iscsi_extra_response *er;
	struct iscsi_param *param;

	output_buf = textbuf + *length;

	if (iscsi_enforce_integrity_rules(phase, param_list) < 0)
		return -1;

	list_for_each_entry(param, &param_list->param_list, p_list) {
		if (!(param->sender & sender))
			continue;
		if (IS_PSTATE_ACCEPTOR(param) &&
		    !IS_PSTATE_RESPONSE_SENT(param) &&
		    !IS_PSTATE_REPLY_OPTIONAL(param) &&
		    (param->phase & phase)) {
			*length += sprintf(output_buf, "%s=%s",
				param->name, param->value);
			*length += 1;
			output_buf = textbuf + *length;
			SET_PSTATE_RESPONSE_SENT(param);
			pr_debug("Sending key: %s=%s\n",
				param->name, param->value);
			continue;
		}
		if (IS_PSTATE_NEGOTIATE(param) &&
		    !IS_PSTATE_ACCEPTOR(param) &&
		    !IS_PSTATE_PROPOSER(param) &&
		    (param->phase & phase)) {
			*length += sprintf(output_buf, "%s=%s",
				param->name, param->value);
			*length += 1;
			output_buf = textbuf + *length;
			SET_PSTATE_PROPOSER(param);
			iscsi_check_proposer_for_optional_reply(param);
			pr_debug("Sending key: %s=%s\n",
				param->name, param->value);
		}
	}

	list_for_each_entry(er, &param_list->extra_response_list, er_list) {
		*length += sprintf(output_buf, "%s=%s", er->key, er->value);
		*length += 1;
		output_buf = textbuf + *length;
		pr_debug("Sending key: %s=%s\n", er->key, er->value);
	}
	iscsi_release_extra_responses(param_list);

	return 0;
}

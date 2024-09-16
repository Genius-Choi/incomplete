int qeth_query_oat_command(struct qeth_card *card, char __user *udata)
{
	int rc = 0;
	struct qeth_cmd_buffer *iob;
	struct qeth_ipa_cmd *cmd;
	struct qeth_query_oat *oat_req;
	struct qeth_query_oat_data oat_data;
	struct qeth_qoat_priv priv;
	void __user *tmp;

	QETH_CARD_TEXT(card, 3, "qoatcmd");

	if (!qeth_adp_supported(card, IPA_SETADP_QUERY_OAT)) {
		rc = -EOPNOTSUPP;
		goto out;
	}

	if (copy_from_user(&oat_data, udata,
	    sizeof(struct qeth_query_oat_data))) {
			rc = -EFAULT;
			goto out;
	}

	priv.buffer_len = oat_data.buffer_len;
	priv.response_len = 0;
	priv.buffer =  kzalloc(oat_data.buffer_len, GFP_KERNEL);
	if (!priv.buffer) {
		rc = -ENOMEM;
		goto out;
	}

	iob = qeth_get_adapter_cmd(card, IPA_SETADP_QUERY_OAT,
				   sizeof(struct qeth_ipacmd_setadpparms_hdr) +
				   sizeof(struct qeth_query_oat));
	cmd = (struct qeth_ipa_cmd *)(iob->data+IPA_PDU_HEADER_SIZE);
	oat_req = &cmd->data.setadapterparms.data.query_oat;
	oat_req->subcmd_code = oat_data.command;

	rc = qeth_send_ipa_cmd(card, iob, qeth_setadpparms_query_oat_cb,
			       &priv);
	if (!rc) {
		if (is_compat_task())
			tmp = compat_ptr(oat_data.ptr);
		else
			tmp = (void __user *)(unsigned long)oat_data.ptr;

		if (copy_to_user(tmp, priv.buffer,
		    priv.response_len)) {
			rc = -EFAULT;
			goto out_free;
		}

		oat_data.response_len = priv.response_len;

		if (copy_to_user(udata, &oat_data,
		    sizeof(struct qeth_query_oat_data)))
			rc = -EFAULT;
	} else
		if (rc == IPA_RC_FFFF)
			rc = -EFAULT;

out_free:
	kfree(priv.buffer);
out:
	return rc;
}

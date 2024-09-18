authentic_parse_credential_data(struct sc_context *ctx, struct sc_pin_cmd_data *pin_cmd,
		unsigned char *blob, size_t blob_len)
{
	unsigned char *data;
	size_t data_len;
	int rv, ii;
	unsigned tag = AUTHENTIC_TAG_CREDENTIAL | pin_cmd->pin_reference;

	rv = authentic_get_tagged_data(ctx, blob, blob_len, tag, &blob, &blob_len);
	LOG_TEST_RET(ctx, rv, "cannot get credential data");

	rv = authentic_get_tagged_data(ctx, blob, blob_len, AUTHENTIC_TAG_CREDENTIAL_TRYLIMIT, &data, &data_len);
	LOG_TEST_RET(ctx, rv, "cannot get try limit");
	pin_cmd->pin1.max_tries = *data;

	rv = authentic_get_tagged_data(ctx, blob, blob_len, AUTHENTIC_TAG_DOCP_MECH, &data, &data_len);
	LOG_TEST_RET(ctx, rv, "cannot get PIN type");
	if (*data == 0)
		pin_cmd->pin_type = SC_AC_CHV;
	else if (*data >= 2 && *data <= 7)
		pin_cmd->pin_type = SC_AC_AUT;
	else
		LOG_TEST_RET(ctx, SC_ERROR_NOT_SUPPORTED, "unsupported Credential type");

	rv = authentic_get_tagged_data(ctx, blob, blob_len, AUTHENTIC_TAG_DOCP_ACLS, &data, &data_len);
	LOG_TEST_RET(ctx, rv, "failed to get ACLs");
	sc_log(ctx, "data_len:%"SC_FORMAT_LEN_SIZE_T"u", data_len);
	if (data_len == 10)   {
		for (ii=0; ii<5; ii++)   {
			unsigned char acl = *(data + ii*2);
			unsigned char cred_id = *(data + ii*2 + 1);
			unsigned sc = acl * 0x100 + cred_id;

			sc_log(ctx, "%i: SC:%X", ii, sc);
			if (!sc)
				continue;

			if (acl & AUTHENTIC_AC_SM_MASK)   {
				pin_cmd->pin1.acls[ii].method = SC_AC_SCB;
				pin_cmd->pin1.acls[ii].key_ref = sc;
			}
			else if (acl!=0xFF && cred_id)   {
				sc_log(ctx, "%i: ACL(method:SC_AC_CHV,id:%i)", ii, cred_id);
				pin_cmd->pin1.acls[ii].method = SC_AC_CHV;
				pin_cmd->pin1.acls[ii].key_ref = cred_id;
			}
			else   {
				pin_cmd->pin1.acls[ii].method = SC_AC_NEVER;
				pin_cmd->pin1.acls[ii].key_ref = 0;
			}
		}
	}

	rv = authentic_get_tagged_data(ctx, blob, blob_len, AUTHENTIC_TAG_CREDENTIAL_PINPOLICY, &data, &data_len);
	if (!rv)   {
		blob = data;
		blob_len = data_len;

		rv = authentic_get_tagged_data(ctx, blob, blob_len, AUTHENTIC_TAG_CREDENTIAL_PINPOLICY_MAXLENGTH, &data, &data_len);
		LOG_TEST_RET(ctx, rv, "failed to get PIN max.length value");
		pin_cmd->pin1.max_length = *data;

		rv = authentic_get_tagged_data(ctx, blob, blob_len, AUTHENTIC_TAG_CREDENTIAL_PINPOLICY_MINLENGTH, &data, &data_len);
		LOG_TEST_RET(ctx, rv, "failed to get PIN min.length value");
		pin_cmd->pin1.min_length = *data;
	}

	return SC_SUCCESS;
}

authentic_pin_verify(struct sc_card *card, struct sc_pin_cmd_data *pin_cmd)
{
	struct sc_context *ctx = card->ctx;
	struct authentic_private_data *prv_data = (struct authentic_private_data *) card->drv_data;
	unsigned char pin_sha1[SHA_DIGEST_LENGTH];
	int rv;

	LOG_FUNC_CALLED(ctx);
	sc_log(ctx, "PIN(type:%X,reference:%X,data:%p,length:%i)",
			pin_cmd->pin_type, pin_cmd->pin_reference, pin_cmd->pin1.data, pin_cmd->pin1.len);

	if (pin_cmd->pin1.data && !pin_cmd->pin1.len)   {
		pin_cmd->pin1.tries_left = -1;
		rv = authentic_pin_is_verified(card, pin_cmd, &pin_cmd->pin1.tries_left);
		LOG_FUNC_RETURN(ctx, rv);
	}

	if (pin_cmd->pin1.data)
		SHA1(pin_cmd->pin1.data, pin_cmd->pin1.len, pin_sha1);
	else
		SHA1((unsigned char *)"", 0, pin_sha1);

	if (!memcmp(pin_sha1, prv_data->pins_sha1[pin_cmd->pin_reference], SHA_DIGEST_LENGTH))   {
		sc_log(ctx, "Already verified");
		LOG_FUNC_RETURN(ctx, SC_SUCCESS);
	}

	memset(prv_data->pins_sha1[pin_cmd->pin_reference], 0, sizeof(prv_data->pins_sha1[0]));

	rv = authentic_pin_get_policy(card, pin_cmd);
	LOG_TEST_RET(ctx, rv, "Get 'PIN policy' error");

	if (pin_cmd->pin1.len > (int)pin_cmd->pin1.max_length)
		LOG_TEST_RET(ctx, SC_ERROR_INVALID_PIN_LENGTH, "PIN policy check failed");

	pin_cmd->pin1.tries_left = -1;
	rv = authentic_chv_verify(card, pin_cmd, &pin_cmd->pin1.tries_left);
	LOG_TEST_RET(ctx, rv, "PIN CHV verification error");

	memcpy(prv_data->pins_sha1[pin_cmd->pin_reference], pin_sha1, SHA_DIGEST_LENGTH);
	LOG_FUNC_RETURN(ctx, rv);
}

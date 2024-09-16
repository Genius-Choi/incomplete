auth_logout(struct sc_card *card)
{
	struct sc_apdu apdu;
	int ii, rv = 0, pin_ref;
	int reset_flag = 0x20;

	for (ii=0; ii < 4; ii++)   {
		rv = auth_get_pin_reference (card, SC_AC_CHV, ii+1, SC_PIN_CMD_UNBLOCK, &pin_ref);
		LOG_TEST_RET(card->ctx, rv, "Cannot get PIN reference");

		sc_format_apdu(card, &apdu, SC_APDU_CASE_1, 0x2E, 0x00, 0x00);
		apdu.cla = 0x80;
		apdu.p2 = pin_ref | reset_flag;
		rv = sc_transmit_apdu(card, &apdu);
		LOG_TEST_RET(card->ctx, rv, "APDU transmit failed");

	}

	LOG_FUNC_RETURN(card->ctx, rv);
}

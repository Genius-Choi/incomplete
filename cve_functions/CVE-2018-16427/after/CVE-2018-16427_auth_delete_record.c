auth_delete_record(struct sc_card *card, unsigned int nr_rec)
{
	struct sc_apdu apdu;
	int rv = 0;

	LOG_FUNC_CALLED(card->ctx);
	sc_log(card->ctx, "auth_delete_record(): nr_rec %i", nr_rec);

	sc_format_apdu(card, &apdu, SC_APDU_CASE_1, 0x32, nr_rec, 0x04);
	apdu.cla = 0x80;

	rv = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(card->ctx, rv, "APDU transmit failed");

	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_FUNC_RETURN(card->ctx, rv);
}

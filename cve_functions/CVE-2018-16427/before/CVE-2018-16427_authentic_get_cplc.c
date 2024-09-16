authentic_get_cplc(struct sc_card *card)
{
	struct authentic_private_data *prv_data = (struct authentic_private_data *) card->drv_data;
	struct sc_apdu apdu;
	int rv, ii;
	unsigned char p1, p2;

	p1 = (SC_CPLC_TAG >> 8) & 0xFF;
	p2 = SC_CPLC_TAG & 0xFF;
	sc_format_apdu(card, &apdu, SC_APDU_CASE_2_SHORT, 0xCA, p1, p2);
	for (ii=0;ii<2;ii++)   {
		apdu.le = SC_CPLC_DER_SIZE;
		apdu.resplen = sizeof(prv_data->cplc.value);
		apdu.resp = prv_data->cplc.value;

		rv = sc_transmit_apdu(card, &apdu);
		LOG_TEST_RET(card->ctx, rv, "APDU transmit failed");
		rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
		if (rv != SC_ERROR_CLASS_NOT_SUPPORTED)
			break;

		apdu.cla = 0x80;
	}
        LOG_TEST_RET(card->ctx, rv, "'GET CPLC' error");

	prv_data->cplc.len = SC_CPLC_DER_SIZE;
	return SC_SUCCESS;
}

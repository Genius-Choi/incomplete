static int entersafe_get_serialnr(sc_card_t *card, sc_serial_number_t *serial)
{
	int	r;
	sc_apdu_t apdu;
	u8 rbuf[SC_MAX_APDU_BUFFER_SIZE];

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);
	assert(serial);

	sc_format_apdu(card, &apdu, SC_APDU_CASE_2_SHORT,0xEA,0x00,0x00);
	apdu.cla=0x80;
	apdu.resp=rbuf;
	apdu.resplen=sizeof(rbuf);
	apdu.le=0x08;

	r=entersafe_transmit_apdu(card, &apdu,0,0,0,0);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, sc_check_sw(card,apdu.sw1,apdu.sw2),"EnterSafe get SN failed");

	card->serialnr.len=serial->len=8;
	memcpy(card->serialnr.value,rbuf,8);
	memcpy(serial->value,rbuf,8);

	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE,SC_SUCCESS);
}

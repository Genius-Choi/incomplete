static int entersafe_update_binary(sc_card_t *card,
								   unsigned int idx, const u8 *buf,
								   size_t count, unsigned long flags)
{
	sc_apdu_t apdu;
	int r;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	assert(count <= card->max_send_size);

	sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0xD6,
		       (idx >> 8) & 0xFF, idx & 0xFF);
	apdu.cla=idx > 0x7fff ? 0x80:0x00;
	apdu.lc = count;
	apdu.datalen = count;
	apdu.data = buf;

	r = entersafe_transmit_apdu(card, &apdu,0,0,0,0);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, sc_check_sw(card, apdu.sw1, apdu.sw2),
		    "Card returned error");
	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, count);
}

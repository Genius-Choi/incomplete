static int entersafe_compute_with_prkey(sc_card_t *card,
										const u8 * data, size_t datalen,
										u8 * out, size_t outlen)
{
	int r;
	sc_apdu_t apdu;
	u8 sbuf[SC_MAX_APDU_BUFFER_SIZE];
	u8 rbuf[SC_MAX_APDU_BUFFER_SIZE];
	u8* p=sbuf;
	size_t size = datalen;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	if(!data)
		 SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE,SC_ERROR_INVALID_ARGUMENTS);

	memcpy(p,data,size);

	if(!card->drv_data)
		 SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE,SC_ERROR_INTERNAL);

	r = entersafe_internal_set_security_env(card,card->drv_data,&p,&size);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "internal set security env failed");
   
	sc_format_apdu(card, &apdu, SC_APDU_CASE_4_SHORT, 0x2A, 0x86,0x80);
	apdu.data=p;
	apdu.lc = size;
	apdu.datalen = size;
	apdu.resp = rbuf;
	apdu.resplen = sizeof(rbuf);
	apdu.le = 256;

	r = entersafe_transmit_apdu(card, &apdu,0,0,0,0);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");

	if (apdu.sw1 == 0x90 && apdu.sw2 == 0x00) {
		size_t len = apdu.resplen > outlen ? outlen : apdu.resplen;
		memcpy(out, apdu.resp, len);
		SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, len);
	}
	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, sc_check_sw(card, apdu.sw1, apdu.sw2));
}

gpk_hash(sc_card_t *card, const u8 *data, size_t datalen)
{
	sc_apdu_t	apdu;
	unsigned int	count, chain, len;
	int		r;

	chain = 0x01;
	for (count = 0; count < datalen; count += len) {
		unsigned char	buffer[GPK_HASH_CHUNK+2];

		if ((len = datalen - count) > GPK_HASH_CHUNK)
			len = GPK_HASH_CHUNK;
		else
			chain |= 0x10;
		buffer[0] = 0x55;
		buffer[1] = len;
		memcpy(buffer+2, data + count, len);

		memset(&apdu, 0, sizeof(apdu));
		apdu.cse = SC_APDU_CASE_3_SHORT;
		apdu.cla = 0x80;
		apdu.ins = 0xDA;
		apdu.p1  = chain;
		apdu.p2  = len;
		apdu.lc  = len + 2;
		apdu.data= buffer;
		apdu.datalen = len + 2;

		r = sc_transmit_apdu(card, &apdu);
		SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
		r = sc_check_sw(card, apdu.sw1, apdu.sw2);
		SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "Card returned error");
		chain = 0;
	}

	return 0;
}

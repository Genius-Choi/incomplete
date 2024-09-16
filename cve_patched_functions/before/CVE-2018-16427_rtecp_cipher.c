static int rtecp_cipher(sc_card_t *card, const u8 *data, size_t data_len,
		u8 *out, size_t out_len, int sign)
{
	sc_apdu_t apdu;
	u8 *buf, *buf_out;
	size_t i;
	int r;

	assert(card && card->ctx && data && out);
	buf_out = malloc(out_len + 2);
	buf = malloc(data_len);
	if (!buf || !buf_out)
	{
		free(buf);
		free(buf_out);
		SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_NORMAL, SC_ERROR_OUT_OF_MEMORY);
	}

	for (i = 0; i < data_len; ++i)
		buf[i] = data[data_len - 1 - i];

	if (sign)
		sc_format_apdu(card, &apdu, SC_APDU_CASE_4_SHORT, 0x2A, 0x9E, 0x9A);
	else
		sc_format_apdu(card, &apdu, SC_APDU_CASE_4_SHORT, 0x2A, 0x80, 0x86);
	apdu.lc = data_len;
	apdu.data = buf;
	apdu.datalen = data_len;
	apdu.resp = buf_out;
	apdu.resplen = out_len + 2;
	apdu.le = out_len > 256 ? 256 : out_len;
	if (apdu.lc > 255)
		apdu.flags |= SC_APDU_FLAGS_CHAINING;
	r = sc_transmit_apdu(card, &apdu);
	if (!sign)
	{
		assert(buf);
		sc_mem_clear(buf, data_len);
	}
	assert(buf);
	free(buf);
	if (r)
		sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL, "APDU transmit failed: %s\n", sc_strerror(r));
	else
	{
		if (apdu.sw1 == 0x90 && apdu.sw2 == 0x00)
		{
			assert(buf_out);
			for (i = 0; i < apdu.resplen; ++i)
				out[i] = buf_out[apdu.resplen - 1 - i];
			r = (i > 0) ? (int)i : SC_ERROR_INTERNAL;
		}
		else
			r = sc_check_sw(card, apdu.sw1, apdu.sw2);
	}
	if (!sign)
	{
		assert(buf_out);
		sc_mem_clear(buf_out, out_len + 2);
	}
	assert(buf_out);
	free(buf_out);
	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, r);

}

static int send_apdu(void)
{
	sc_apdu_t apdu;
	u8 buf[SC_MAX_EXT_APDU_BUFFER_SIZE],
	  rbuf[SC_MAX_EXT_APDU_BUFFER_SIZE];
	size_t len0, r;
	int c;

	for (c = 0; c < opt_apdu_count; c++) {
		len0 = sizeof(buf);
		sc_hex_to_bin(opt_apdus[c], buf, &len0);

		r = sc_bytes2apdu(card->ctx, buf, len0, &apdu);
		if (r) {
			fprintf(stderr, "Invalid APDU: %s\n", sc_strerror(r));
			return 2;
		}

		apdu.resp = rbuf;
		apdu.resplen = sizeof(rbuf);

		printf("Sending: ");
		for (r = 0; r < len0; r++)
			printf("%02X ", buf[r]);
		printf("\n");
		r = sc_lock(card);
		if (r == SC_SUCCESS)
			r = sc_transmit_apdu(card, &apdu);
		sc_unlock(card);
		if (r) {
			fprintf(stderr, "APDU transmit failed: %s\n", sc_strerror(r));
			return 1;
		}
		printf("Received (SW1=0x%02X, SW2=0x%02X)%s\n", apdu.sw1, apdu.sw2,
		      apdu.resplen ? ":" : "");
		if (apdu.resplen)
			util_hex_dump_asc(stdout, apdu.resp, apdu.resplen, -1);
	}
	return 0;
}

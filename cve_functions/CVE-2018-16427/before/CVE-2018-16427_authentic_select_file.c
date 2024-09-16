authentic_select_file(struct sc_card *card, const struct sc_path *path,
		 struct sc_file **file_out)
{
	struct sc_context *ctx = card->ctx;
	struct sc_apdu apdu;
	struct sc_path lpath;
	unsigned char rbuf[SC_MAX_APDU_BUFFER_SIZE];
	int pathlen, rv;

	LOG_FUNC_CALLED(ctx);
	authentic_debug_select_file(card, path);

	memcpy(&lpath, path, sizeof(struct sc_path));

	rv = authentic_reduce_path(card, &lpath);
	LOG_TEST_RET(ctx, rv, "reduce path error");

	if (lpath.len >= 2 && lpath.value[0] == 0x3F && lpath.value[1] == 0x00)   {
		rv = authentic_select_mf(card, file_out);
		LOG_TEST_RET(ctx, rv, "cannot select MF");

		memmove(&lpath.value[0], &lpath.value[2], lpath.len - 2);
		lpath.len -=  2;

		if (!lpath.len)
			LOG_FUNC_RETURN(ctx, SC_SUCCESS);
	}

	if (lpath.type == SC_PATH_TYPE_PATH && (lpath.len == 2))
		lpath.type = SC_PATH_TYPE_FILE_ID;

	rv = authentic_is_selected(card, &lpath, file_out);
	if (!rv)
		LOG_FUNC_RETURN(ctx, SC_SUCCESS);

	pathlen = lpath.len;
	sc_format_apdu(card, &apdu, SC_APDU_CASE_4_SHORT, 0xA4, 0x00, 0x00);

	if (card->type != SC_CARD_TYPE_OBERTHUR_AUTHENTIC_3_2)
		LOG_TEST_RET(ctx, SC_ERROR_NOT_SUPPORTED, "Unsupported card");

	if (lpath.type == SC_PATH_TYPE_FILE_ID)   {
		apdu.p1 = 0x00;
	}
	else if (lpath.type == SC_PATH_TYPE_PATH)  {
		apdu.p1 = 0x08;
	}
	else if (lpath.type == SC_PATH_TYPE_FROM_CURRENT)  {
		apdu.p1 = 0x09;
	}
	else if (lpath.type == SC_PATH_TYPE_DF_NAME)   {
		apdu.p1 = 4;
	}
	else if (lpath.type == SC_PATH_TYPE_PARENT)   {
		apdu.p1 = 0x03;
		pathlen = 0;
		apdu.cse = SC_APDU_CASE_2_SHORT;
	}
	else   {
		sc_log(ctx, "Invalid PATH type: 0x%X", lpath.type);
		LOG_TEST_RET(ctx, SC_ERROR_NOT_SUPPORTED, "authentic_select_file() invalid PATH type");
	}

	apdu.lc = pathlen;
	apdu.data = lpath.value;
	apdu.datalen = pathlen;

	if (apdu.cse == SC_APDU_CASE_4_SHORT || apdu.cse == SC_APDU_CASE_2_SHORT)   {
		apdu.resp = rbuf;
		apdu.resplen = sizeof(rbuf);
		apdu.le = 256;
	}

	rv = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(ctx, rv, "APDU transmit failed");
	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_TEST_RET(ctx, rv, "authentic_select_file() check SW failed");

	rv = authentic_set_current_files(card, &lpath, apdu.resp, apdu.resplen, file_out);
	LOG_TEST_RET(ctx, rv, "authentic_select_file() cannot set 'current_file'");

	LOG_FUNC_RETURN(ctx, SC_SUCCESS);
}

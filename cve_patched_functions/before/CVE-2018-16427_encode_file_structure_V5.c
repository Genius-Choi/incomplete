encode_file_structure_V5(struct sc_card *card, const struct sc_file *file,
				 unsigned char *buf, size_t *buflen)
{
	size_t ii;
	int rv=0, size;
	unsigned char *p = buf;
	unsigned char  ops[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

	LOG_FUNC_CALLED(card->ctx);
	sc_log(card->ctx,
	       "id %04X; size %"SC_FORMAT_LEN_SIZE_T"u; type 0x%X/0x%X",
	       file->id, file->size, file->type, file->ef_structure);

	if (*buflen < 0x18)
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_INCORRECT_PARAMETERS);

	p[0] = 0x62, p[1] = 0x16;
	p[2] = 0x82, p[3] = 0x02;

	rv = 0;
	if (file->type == SC_FILE_TYPE_DF)  {
		p[4] = 0x38;
		p[5] = 0x00;
	}
	else  if (file->type == SC_FILE_TYPE_WORKING_EF)   {
		switch (file->ef_structure) {
		case SC_FILE_EF_TRANSPARENT:
			p[4] = 0x01;
			p[5] = 0x01;
			break;
		case SC_FILE_EF_LINEAR_VARIABLE:
			p[4] = 0x04;
			p[5] = 0x01;
			break;
		default:
			rv = SC_ERROR_INVALID_ARGUMENTS;
			break;
		}
	}
	else if (file->type == SC_FILE_TYPE_INTERNAL_EF)  {
		switch (file->ef_structure) {
		case SC_CARDCTL_OBERTHUR_KEY_DES:
			p[4] = 0x11;
			p[5] = 0x00;
			break;
		case SC_CARDCTL_OBERTHUR_KEY_RSA_PUBLIC:
			p[4] = 0x12;
			p[5] = 0x00;
			break;
		case SC_CARDCTL_OBERTHUR_KEY_RSA_CRT:
			p[4] = 0x14;
			p[5] = 0x00;
			break;
		default:
			rv = -1;
			break;
		}
	}
	else
		rv = SC_ERROR_INVALID_ARGUMENTS;

	if (rv)   {
		sc_log(card->ctx, "Invalid EF structure 0x%X/0x%X", file->type, file->ef_structure);
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_INCORRECT_PARAMETERS);
	}

	p[6] = 0x83;
	p[7] = 0x02;
	p[8] = file->id >> 8;
	p[9] = file->id & 0xFF;

	p[10] = 0x85;
	p[11] = 0x02;

	size = file->size;

	if (file->type == SC_FILE_TYPE_DF)   {
		size &= 0xFF;
	}
	else if (file->type == SC_FILE_TYPE_INTERNAL_EF &&
			file->ef_structure == SC_CARDCTL_OBERTHUR_KEY_RSA_PUBLIC)   {
		sc_log(card->ctx, "ef %s","SC_FILE_EF_RSA_PUBLIC");
		if (file->size == PUBKEY_512_ASN1_SIZE || file->size == 512)
			size = 512;
		else if (file->size == PUBKEY_1024_ASN1_SIZE || file->size == 1024)
			size = 1024;
		else if (file->size == PUBKEY_2048_ASN1_SIZE || file->size == 2048)
			size = 2048;
		else   {
			sc_log(card->ctx,
			       "incorrect RSA size %"SC_FORMAT_LEN_SIZE_T"X",
			       file->size);
			LOG_FUNC_RETURN(card->ctx, SC_ERROR_INCORRECT_PARAMETERS);
		}
	}
	else if (file->type == SC_FILE_TYPE_INTERNAL_EF &&
			file->ef_structure == SC_CARDCTL_OBERTHUR_KEY_DES)   {
		if (file->size == 8 || file->size == 64)
			size = 64;
		else if (file->size == 16 || file->size == 128)
			size = 128;
		else if (file->size == 24 || file->size == 192)
			size = 192;
		else   {
			sc_log(card->ctx,
			       "incorrect DES size %"SC_FORMAT_LEN_SIZE_T"u",
			       file->size);
			LOG_FUNC_RETURN(card->ctx, SC_ERROR_INCORRECT_PARAMETERS);
		}
	}

	p[12] = (size >> 8) & 0xFF;
	p[13] = size & 0xFF;

	p[14] = 0x86;
	p[15] = 0x08;

	if (file->type == SC_FILE_TYPE_DF) {
		ops[0] = SC_AC_OP_CREATE;
		ops[1] = SC_AC_OP_CRYPTO;
		ops[2] = SC_AC_OP_LIST_FILES;
		ops[3] = SC_AC_OP_DELETE;
		ops[4] = SC_AC_OP_PIN_DEFINE;
		ops[5] = SC_AC_OP_PIN_CHANGE;
		ops[6] = SC_AC_OP_PIN_RESET;
	}
	else if (file->type == SC_FILE_TYPE_WORKING_EF)   {
		if (file->ef_structure == SC_FILE_EF_TRANSPARENT)   {
			sc_log(card->ctx, "SC_FILE_EF_TRANSPARENT");
			ops[0] = SC_AC_OP_WRITE;
			ops[1] = SC_AC_OP_UPDATE;
			ops[2] = SC_AC_OP_READ;
			ops[3] = SC_AC_OP_ERASE;
		}
		else if (file->ef_structure == SC_FILE_EF_LINEAR_VARIABLE)  {
			sc_log(card->ctx, "SC_FILE_EF_LINEAR_VARIABLE");
			ops[0] = SC_AC_OP_WRITE;
			ops[1] = SC_AC_OP_UPDATE;
			ops[2] = SC_AC_OP_READ;
			ops[3] = SC_AC_OP_ERASE;
		}
	}
	else   if (file->type == SC_FILE_TYPE_INTERNAL_EF)   {
		if (file->ef_structure == SC_CARDCTL_OBERTHUR_KEY_DES)  {
			sc_log(card->ctx, "EF_DES");
			ops[0] = SC_AC_OP_UPDATE;
			ops[1] = SC_AC_OP_PSO_DECRYPT;
			ops[2] = SC_AC_OP_PSO_ENCRYPT;
			ops[3] = SC_AC_OP_PSO_COMPUTE_CHECKSUM;
			ops[4] = SC_AC_OP_PSO_VERIFY_CHECKSUM;
			ops[5] = SC_AC_OP_INTERNAL_AUTHENTICATE;
			ops[6] = SC_AC_OP_EXTERNAL_AUTHENTICATE;
		}
		else if (file->ef_structure == SC_CARDCTL_OBERTHUR_KEY_RSA_PUBLIC)  {
			sc_log(card->ctx, "EF_RSA_PUBLIC");
			ops[0] = SC_AC_OP_UPDATE;
			ops[2] = SC_AC_OP_PSO_ENCRYPT;
			ops[4] = SC_AC_OP_PSO_VERIFY_SIGNATURE;
			ops[6] = SC_AC_OP_EXTERNAL_AUTHENTICATE;
		}
		else if (file->ef_structure == SC_CARDCTL_OBERTHUR_KEY_RSA_CRT)  {
			sc_log(card->ctx, "EF_RSA_PRIVATE");
			ops[0] = SC_AC_OP_UPDATE;
			ops[1] = SC_AC_OP_PSO_DECRYPT;
			ops[3] = SC_AC_OP_PSO_COMPUTE_SIGNATURE;
			ops[5] = SC_AC_OP_INTERNAL_AUTHENTICATE;
		}
	}

	for (ii = 0; ii < sizeof(ops); ii++) {
		const struct sc_acl_entry *entry;

		p[16+ii] = 0xFF;
		if (ops[ii]==0xFF)
			continue;
		entry = sc_file_get_acl_entry(file, ops[ii]);
		rv = acl_to_ac_byte(card,entry);
		LOG_TEST_RET(card->ctx, rv, "Invalid ACL");
		p[16+ii] = rv;
	}

	*buflen = 0x18;

	LOG_FUNC_RETURN(card->ctx, SC_SUCCESS);
}

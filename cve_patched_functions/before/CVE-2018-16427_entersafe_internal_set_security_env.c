static int entersafe_internal_set_security_env(sc_card_t *card,
											   const sc_security_env_t *env,
											   u8 ** data,size_t* size)
{
	sc_apdu_t apdu;
	u8 sbuf[SC_MAX_APDU_BUFFER_SIZE];
	u8 *p=sbuf;
	int r;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	assert(card != NULL && env != NULL);
	
	switch (env->operation) {
	case SC_SEC_OPERATION_DECIPHER:
	case SC_SEC_OPERATION_SIGN:
		 sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0x22, 0, 0);
		 apdu.p1 = 0x41;
		 apdu.p2 = 0xB8;
		 *p++ = 0x80;
		 *p++ = 0x01;
		 *p++ = 0x80;
		 *p++ = 0x83;
		 *p++ = 0x02;
		 *p++ = env->key_ref[0];
		 *p++ = 0x22;
		 if(*size>1024/8)
		 {
			  if(*size == 2048/8)
			  {
				   *p++ = 0x89;
				   *p++ = 0x40;
				   memcpy(p,*data,0x40);
				   p+=0x40;
				   *data+=0x40;
				   *size-=0x40;
			  }
			  else
			  {
				   SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, SC_ERROR_INVALID_ARGUMENTS);
			  }
		 }
		 break;
	default:
		 SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, SC_ERROR_INVALID_ARGUMENTS);
	}
	
	apdu.le = 0;
	apdu.lc = apdu.datalen = p - sbuf;
	apdu.data = sbuf;
	apdu.resplen = 0;

	r = sc_transmit_apdu(card, &apdu);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	return sc_check_sw(card, apdu.sw1, apdu.sw2);
}

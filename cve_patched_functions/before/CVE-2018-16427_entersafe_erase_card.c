static int entersafe_erase_card(sc_card_t *card)
{
	int r;
	u8  sbuf[2];
	sc_apdu_t apdu;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	sbuf[0] = 0x3f;
	sbuf[1] = 0x00;
	sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0xA4, 0x00, 0x00);
	apdu.lc   = 2;
	apdu.datalen = 2;
	apdu.data = sbuf;
	
	r = entersafe_transmit_apdu(card, &apdu,0,0,0,0);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	sc_invalidate_cache(card);

	sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0xEE, 0x00, 0x00);
	apdu.cla=0x84;
	apdu.lc=2;
	apdu.datalen=2;
	apdu.data=sbuf;

	switch(card->type)
	{
	case SC_CARD_TYPE_ENTERSAFE_3K:
	{
		 r = entersafe_transmit_apdu(card, &apdu,trans_code_3k,sizeof(trans_code_3k),0,1);
	}break;
	case SC_CARD_TYPE_ENTERSAFE_FTCOS_PK_01C:
	case SC_CARD_TYPE_ENTERSAFE_EJAVA_PK_01C:
	case SC_CARD_TYPE_ENTERSAFE_EJAVA_PK_01C_T0:		
	case SC_CARD_TYPE_ENTERSAFE_EJAVA_H10CR_PK_01C_T1:
	case SC_CARD_TYPE_ENTERSAFE_EJAVA_D11CR_PK_01C_T1:
	case SC_CARD_TYPE_ENTERSAFE_EJAVA_C21C_PK_01C_T1:
	case SC_CARD_TYPE_ENTERSAFE_EJAVA_A22CR_PK_01C_T1:
	case SC_CARD_TYPE_ENTERSAFE_EJAVA_A40CR_PK_01C_T1:
	{
		 r = entersafe_transmit_apdu(card, &apdu,trans_code_ftcos_pk_01c,sizeof(trans_code_ftcos_pk_01c),0,1);
	}break;
	default:
	{
		 r = SC_ERROR_INTERNAL;
	}break;
	}

	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, sc_check_sw(card, apdu.sw1, apdu.sw2));
}

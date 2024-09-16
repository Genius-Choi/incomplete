static int entersafe_create_mf(sc_card_t *card, sc_entersafe_create_data * data)
{
	int r;
	sc_apdu_t apdu;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	memcpy(data->data.df.init_key, init_key, sizeof(init_key));

	sc_format_apdu(card,&apdu,SC_APDU_CASE_3_SHORT,0xE0,0x00,0x00);
	apdu.cla=0x84;
	apdu.data=(u8*)&data->data.df;
	apdu.datalen=apdu.lc=sizeof(data->data.df);

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
	return sc_check_sw(card, apdu.sw1, apdu.sw2);
}

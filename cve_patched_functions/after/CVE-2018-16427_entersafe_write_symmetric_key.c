static int entersafe_write_symmetric_key(sc_card_t *card,
										 u8 key_id,u8 usage,
										 u8 EC,u8 ver,
										 u8 *data,size_t len)
{
	 sc_apdu_t apdu;
	 u8 sbuff[SC_MAX_APDU_BUFFER_SIZE]={0};
	 int r;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	 if(len>240)
		  SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE,SC_ERROR_INCORRECT_PARAMETERS);

	 sbuff[0]=EC;
	 sbuff[1]=ver;
	 memcpy(&sbuff[2],data,len);

	 sc_format_apdu(card,&apdu,SC_APDU_CASE_3_SHORT,0xF4,usage,key_id);
	 apdu.cla=0x84;
	 apdu.data=sbuff;
	 apdu.lc=apdu.datalen=len+2;

	 r=entersafe_transmit_apdu(card,&apdu,key_maintain,sizeof(key_maintain),1,1);
	 SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	 SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, sc_check_sw(card, apdu.sw1, apdu.sw2),"Write prkey failed");
	 SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE,r);
}

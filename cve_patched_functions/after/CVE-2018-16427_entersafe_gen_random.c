static int entersafe_gen_random(sc_card_t *card,u8 *buff,size_t size)
{
	 int r=SC_SUCCESS;
	 u8 rbuf[SC_MAX_APDU_BUFFER_SIZE]={0};
	 sc_apdu_t apdu;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);
   
	 sc_format_apdu(card,&apdu,SC_APDU_CASE_2_SHORT,0x84,0x00,0x00);
	 apdu.resp=rbuf;
	 apdu.le=size;
	 apdu.resplen=sizeof(rbuf);

	 r=sc_transmit_apdu(card,&apdu);
	 SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "entersafe gen random failed");

	 if(apdu.resplen!=size)
		  SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_NORMAL,SC_ERROR_INTERNAL);
	 memcpy(buff,rbuf,size);

	 SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_NORMAL,r);
}

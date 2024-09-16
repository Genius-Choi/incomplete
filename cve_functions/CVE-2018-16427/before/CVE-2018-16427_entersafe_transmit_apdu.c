static int entersafe_transmit_apdu(sc_card_t *card, sc_apdu_t *apdu,
								   u8 * key, size_t keylen,
								   int cipher,int mac)
{
	 u8 *cipher_data=0,*mac_data=0;
	 size_t cipher_data_size,mac_data_size;
	 int blocks;
	 int r=SC_SUCCESS;
	u8 *sbuf=NULL;
	size_t ssize=0;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	 assert(card);
	 assert(apdu);

	 if((cipher||mac) && (!key||(keylen!=8 && keylen!=16)))
		  SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, SC_ERROR_INVALID_ARGUMENTS);

	r = sc_apdu_get_octets(card->ctx, apdu, &sbuf, &ssize, SC_PROTO_RAW);
	if (r == SC_SUCCESS)
		sc_apdu_log(card->ctx, SC_LOG_DEBUG_VERBOSE, sbuf, ssize, 1);
	if(sbuf)
		free(sbuf);

	 if(cipher)
	 {
		  blocks=(apdu->lc+2)/8+1;
		  cipher_data_size=blocks*8;
		  cipher_data=malloc(cipher_data_size);
		  if(!cipher_data)
		  {
			   r = SC_ERROR_OUT_OF_MEMORY;
			   goto out;
		  }

		  if((r = entersafe_cipher_apdu(card,apdu,key,keylen,cipher_data,cipher_data_size))<0)
			   goto out;
	 }
	 if(mac)
	 {	 
		  mac_data_size=apdu->lc+4;
		  mac_data=malloc(mac_data_size);
		  if(!mac_data)
		  {
			   r = SC_ERROR_OUT_OF_MEMORY;
			   goto out;
		  }
		  r = entersafe_mac_apdu(card,apdu,key,keylen,mac_data,mac_data_size);
		  if(r < 0)
			   goto out;
	 }
	 
	 r = sc_transmit_apdu(card,apdu);

out:
	 if(cipher_data)
		  free(cipher_data);
	 if(mac_data)
		  free(mac_data);

	 SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, r);
}

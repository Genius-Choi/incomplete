static int entersafe_write_key(sc_card_t *card, sc_entersafe_wkey_data *data)
{
	 struct sc_pkcs15_prkey_rsa* rsa=data->key_data.rsa;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	 switch(data->usage)
	 {
	 case 0x22:
		  if(rsa->modulus.len < 256)
			   return entersafe_write_small_rsa_key(card,data->key_id,rsa);
		  else
			   return entersafe_write_large_rsa_key(card,data->key_id,rsa);
		  break;
	 case 0x2A:
		  SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE,SC_ERROR_NOT_SUPPORTED);
		  break;
	 default:
		  return entersafe_write_symmetric_key(card,data->key_id,data->usage,
											   data->key_data.symmetric.EC,
											   data->key_data.symmetric.ver,
											   data->key_data.symmetric.key_val,
											   data->key_data.symmetric.key_len);
		  break;
	 }
	 SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE,SC_SUCCESS);
}

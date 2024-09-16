static int entersafe_compute_signature(sc_card_t *card,
									   const u8 * data, size_t datalen,
									   u8 * out, size_t outlen)
{
	 SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);
	 return entersafe_compute_with_prkey(card,data,datalen,out,outlen);
}

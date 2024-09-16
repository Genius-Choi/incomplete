static int entersafe_decipher(sc_card_t *card,
							  const u8 * crgram, size_t crgram_len,
							  u8 * out, size_t outlen)
{
	 SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);
	 return entersafe_compute_with_prkey(card,crgram,crgram_len,out,outlen);
}

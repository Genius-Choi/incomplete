piv_decipher(sc_card_t *card, const u8 * data, size_t datalen, u8 * out, size_t outlen)
{
	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, piv_validate_general_authentication(card, data, datalen, out, outlen));
}

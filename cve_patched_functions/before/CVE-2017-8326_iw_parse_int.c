IW_IMPL(int) iw_parse_int(const char *s)
{
	double result;
	int charsread;
	iw_parse_number_internal(s, &result, &charsread);
	return iw_round_to_int(result);
}

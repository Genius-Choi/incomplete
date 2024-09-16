_warc_rdtyp(const char *buf, size_t bsz)
{
	static const char _key[] = "\r\nWARC-Type:";
	const char *val, *eol;

	if ((val = xmemmem(buf, bsz, _key, sizeof(_key) - 1U)) == NULL) {
		/* no bother */
		return WT_NONE;
	}
	val += sizeof(_key) - 1U;
	if ((eol = _warc_find_eol(val, buf + bsz - val)) == NULL) {
		/* no end of line */
		return WT_NONE;
	}

	/* overread whitespace */
	while (val < eol && (*val == ' ' || *val == '\t'))
		++val;

	if (val + 8U == eol) {
		if (memcmp(val, "resource", 8U) == 0)
			return WT_RSRC;
		else if (memcmp(val, "response", 8U) == 0)
			return WT_RSP;
	}
	return WT_NONE;
}

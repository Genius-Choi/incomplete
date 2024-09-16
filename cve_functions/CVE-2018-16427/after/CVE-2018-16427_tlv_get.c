tlv_get(const unsigned char *msg, int len, unsigned char tag,
		unsigned char *ret, int *ret_len)
{
	int cur = 0;

	while (cur < len)  {
		if (*(msg+cur)==tag)  {
			int ii, ln = *(msg+cur+1);

			if (ln > *ret_len)
				return SC_ERROR_WRONG_LENGTH;

			for (ii=0; ii<ln; ii++)
				*(ret + ii) = *(msg+cur+2+ii);
			*ret_len = ln;

			return SC_SUCCESS;
		}

		cur += 2 + *(msg+cur+1);
	}

	return SC_ERROR_INCORRECT_PARAMETERS;
}

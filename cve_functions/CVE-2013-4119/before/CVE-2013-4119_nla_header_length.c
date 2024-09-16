UINT32 nla_header_length(wStream* s)
{
	UINT32 length = 0;

	if (s->pointer[1] & 0x80)
	{
		if ((s->pointer[1] & ~(0x80)) == 1)
			length = 3;
		else if ((s->pointer[1] & ~(0x80)) == 2)
			length = 4;
		else
			fprintf(stderr, "Error reading TSRequest!\n");
	}
	else
	{
		length = 2;
	}

	return length;
}

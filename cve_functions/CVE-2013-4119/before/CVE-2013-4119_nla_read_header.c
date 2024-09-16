UINT32 nla_read_header(wStream* s)
{
	UINT32 length = 0;

	if (s->pointer[1] & 0x80)
	{
		if ((s->pointer[1] & ~(0x80)) == 1)
		{
			length = s->pointer[2];
			length += 3;
			Stream_Seek(s, 3);
		}
		else if ((s->pointer[1] & ~(0x80)) == 2)
		{
			length = (s->pointer[2] << 8) | s->pointer[3];
			length += 4;
			Stream_Seek(s, 4);
		}
		else
		{
			fprintf(stderr, "Error reading TSRequest!\n");
		}
	}
	else
	{
		length = s->pointer[1];
		length += 2;
		Stream_Seek(s, 2);
	}

	return length;
}

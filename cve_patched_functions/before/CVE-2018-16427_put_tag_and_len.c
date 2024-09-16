put_tag_and_len(unsigned int tag, size_t len, u8 **ptr)
{
	int i;
	u8 *p;

	if (len < 128) {
		i = 2;
	} else if (len < 256) {
		i = 3;
	} else {
		i = 4;
	}

	if (ptr) {
		p = *ptr;
		*p++ = (u8)tag;
		switch (i) {
			case 2:
				*p++ = len;
				break;
			case 3:
				*p++ = 0x81;
				*p++ = len;
				break;
			case 4:
				*p++ = 0x82;
				*p++ = (u8) (len >> 8);
				*p++ = (u8) (len & 0xff);
				break;
		}
		*ptr = p;
	} else {
		i += len;
	}
	return i;
}

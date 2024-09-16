int password(unsigned char *passwd, size_t length, int flags, int timeout)
{
	unsigned char *buf = passwd;
	int pos = 0;
	unsigned char ch;
	uint64_t start;

	if (!passwd)
		return -EINVAL;

	start = get_time_ns();

	do {
		if (tstc()) {
			ch = getchar();

			switch (ch) {
			case '\r':
			case '\n':
				*buf = '\0';
				puts("\r\n");
				return pos;
			case '\0':
			case '\t':
				continue;
			case CTL_CH('c'):
				passwd[0] = '\0';
				puts("\r\n");
				return -EINTR;
			case CTL_CH('h'):
			case BB_KEY_DEL7:
			case BB_KEY_DEL:
				if (pos > 0) {
					if (flags & STAR)
						puts("\b \b");

					*buf = '\0';
					buf--;
					pos--;
				}
				continue;
			default:
				if (pos < length - 1) {
					if (flags & STAR)
						putchar('*');
					else if (flags & CLEAR)
						putchar(ch);

					*buf = ch;
					buf++;
					pos++;
				} else {
					if (flags & STAR)
						putchar('\a');
				}
			}
		}
	} while (!is_timeout(start, timeout * SECOND) || timeout == 0);

	return -ETIMEDOUT;
}

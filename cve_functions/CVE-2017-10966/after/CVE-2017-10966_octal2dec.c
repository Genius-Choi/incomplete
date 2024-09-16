int octal2dec(int octal)
{
	int dec, n;

	dec = 0; n = 1;
	while (octal != 0) {
		dec += n*(octal%10);
		octal /= 10; n *= 8;
	}

	return dec;
}

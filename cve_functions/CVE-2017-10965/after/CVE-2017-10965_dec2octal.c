int dec2octal(int decimal)
{
	int octal, pos;

	octal = 0; pos = 0;
	while (decimal > 0) {
		octal += (decimal & 7)*(pos == 0 ? 1 : pos);
		decimal /= 8;
		pos += 10;
	}

	return octal;
}

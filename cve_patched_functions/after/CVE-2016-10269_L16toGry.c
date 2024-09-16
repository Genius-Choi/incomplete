L16toGry(LogLuvState* sp, uint8* op, tmsize_t n)
{
	int16* l16 = (int16*) sp->tbuf;
	uint8* gp = (uint8*) op;

	while (n-- > 0) {
		double Y = LogL16toY(*l16++);
		*gp++ = (uint8) ((Y <= 0.) ? 0 : (Y >= 1.) ? 255 : (int)(256.*sqrt(Y)));
	}
}

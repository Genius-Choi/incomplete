L16toY(LogLuvState* sp, uint8* op, tmsize_t n)
{
	int16* l16 = (int16*) sp->tbuf;
	float* yp = (float*) op;

	while (n-- > 0)
		*yp++ = (float)LogL16toY(*l16++);
}

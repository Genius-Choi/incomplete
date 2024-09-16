Luv24fromXYZ(LogLuvState* sp, uint8* op, tmsize_t n)
{
	uint32* luv = (uint32*) sp->tbuf;  
	float* xyz = (float*) op;

	while (n-- > 0) {
		*luv++ = LogLuv24fromXYZ(xyz, sp->encode_meth);
		xyz += 3;
	}
}

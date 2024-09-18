Luv32fromLuv48(LogLuvState* sp, uint8* op, tmsize_t n)
{
	uint32* luv = (uint32*) sp->tbuf;
	int16* luv3 = (int16*) op;

	if (sp->encode_meth == SGILOGENCODE_NODITHER) {
		while (n-- > 0) {
			*luv++ = (uint32)luv3[0] << 16 |
				(luv3[1]*(uint32)(UVSCALE+.5) >> 7 & 0xff00) |
				(luv3[2]*(uint32)(UVSCALE+.5) >> 15 & 0xff);
			luv3 += 3;
		}
		return;
	}
	while (n-- > 0) {
		*luv++ = (uint32)luv3[0] << 16 |
	(itrunc(luv3[1]*(UVSCALE/(1<<15)), sp->encode_meth) << 8 & 0xff00) |
		(itrunc(luv3[2]*(UVSCALE/(1<<15)), sp->encode_meth) & 0xff);
		luv3 += 3;
	}
}

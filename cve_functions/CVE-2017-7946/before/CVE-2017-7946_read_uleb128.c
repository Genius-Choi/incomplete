static ut64 read_uleb128(ulebr *r, ut8 *end) {
	ut64 result = 0;
	int bit = 0;
	ut64 slice = 0;
	ut8 *p = r->p;
	do {
		if (p == end) {
			eprintf ("malformed uleb128");
			break;
		}
		slice = *p & 0x7f;
		if (bit > 63) {
			eprintf ("uleb128 too big for uint64, bit=%d, result=0x%"PFMT64x, bit, result);
		} else {
			result |= (slice << bit);
			bit += 7;
		}
	} while (*p++ & 0x80);
	r->p = p;
	return result;
}

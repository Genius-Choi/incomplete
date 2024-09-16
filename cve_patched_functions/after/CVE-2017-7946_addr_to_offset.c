static ut64 addr_to_offset(struct MACH0_(obj_t)* bin, ut64 addr) {
	ut64 segment_base, segment_size;
	int i;
 
	if (!bin->segs) {
		return 0;
	}
	for (i = 0; i < bin->nsegs; i++) {
		segment_base = (ut64)bin->segs[i].vmaddr;
		segment_size = (ut64)bin->segs[i].vmsize;
		if (addr >= segment_base && addr < segment_base + segment_size) {
			return bin->segs[i].fileoff + (addr - segment_base);
		}
	}
	return 0;
}

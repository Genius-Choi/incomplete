static PE_DWord bin_pe_rva_to_paddr(RBinPEObj* bin, PE_DWord rva) {
	PE_DWord section_base;
	int i, section_size;
	for (i = 0; i < bin->num_sections; i++) {
		section_base = bin->section_header[i].VirtualAddress;
		section_size = bin->section_header[i].Misc.VirtualSize;
		if (rva >= section_base && rva < section_base + section_size) {
			return bin->section_header[i].PointerToRawData + (rva - section_base);
		}
	}
	return rva;
}

static int setup_efi_info_memmap(struct boot_params *params,
				  unsigned long params_load_addr,
				  unsigned int efi_map_offset,
				  unsigned int efi_map_sz)
{
	void *efi_map = (void *)params + efi_map_offset;
	unsigned long efi_map_phys_addr = params_load_addr + efi_map_offset;
	struct efi_info *ei = &params->efi_info;

	if (!efi_map_sz)
		return 0;

	efi_runtime_map_copy(efi_map, efi_map_sz);

	ei->efi_memmap = efi_map_phys_addr & 0xffffffff;
	ei->efi_memmap_hi = efi_map_phys_addr >> 32;
	ei->efi_memmap_size = efi_map_sz;

	return 0;
}

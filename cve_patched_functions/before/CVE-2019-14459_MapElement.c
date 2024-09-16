static uint32_t MapElement(uint16_t Type, uint16_t Length, uint32_t order) {
int	index;

	cache.input_order[order].type	= Type;
	cache.input_order[order].length	= Length;

	index = cache.lookup_info[Type].index;
	if ( index ) {
		while ( index && ipfix_element_map[index].id == Type ) {
			if ( Length == ipfix_element_map[index].length ) {
				cache.lookup_info[Type].found  = 1;
				cache.lookup_info[Type].length = Length;
				cache.lookup_info[Type].index  = index;
				dbg_printf("found extension %u for type: %u, input length: %u output length: %u Extension: %u\n", 
					ipfix_element_map[index].extension, ipfix_element_map[index].id, 
					ipfix_element_map[index].length, ipfix_element_map[index].out_length, ipfix_element_map[index].extension);
				return ipfix_element_map[index].extension;
			}
			index++;
		}
		dbg_printf("Skip known element type: %u, Unknown length: %u\n", Type, Length);
	} else {
		dbg_printf("Skip unknown element type: %u, Length: %u\n", Type, Length);
	}

	cache.input_order[order].type = SKIP_ELEMENT;
	return 0;

} // End of MapElement

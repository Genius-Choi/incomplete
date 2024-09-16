static inline void get_node_id(pegasus_t *pegasus, __u8 *id)
{
	int i;
	__u16 w16;

	for (i = 0; i < 3; i++) {
		read_eprom_word(pegasus, i, &w16);
		((__le16 *) id)[i] = cpu_to_le16(w16);
	}
}

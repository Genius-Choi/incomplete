static void mem_put_le16(char *const mem, const unsigned int val) {
  mem[0] = val;
  mem[1] = val >> 8;
}

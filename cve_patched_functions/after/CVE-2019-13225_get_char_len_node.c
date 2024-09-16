get_char_len_node(Node* node, regex_t* reg, int* len)
{
  return get_char_len_node1(node, reg, len, 0);
}

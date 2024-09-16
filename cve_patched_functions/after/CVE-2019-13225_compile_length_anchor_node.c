compile_length_anchor_node(AnchorNode* node, regex_t* reg)
{
  int len;
  int tlen = 0;

  if (IS_NOT_NULL(NODE_ANCHOR_BODY(node))) {
    tlen = compile_length_tree(NODE_ANCHOR_BODY(node), reg);
    if (tlen < 0) return tlen;
  }

  switch (node->type) {
  case ANCR_PREC_READ:
    len = SIZE_OP_PREC_READ_START + tlen + SIZE_OP_PREC_READ_END;
    break;
  case ANCR_PREC_READ_NOT:
    len = SIZE_OP_PREC_READ_NOT_START + tlen + SIZE_OP_PREC_READ_NOT_END;
    break;
  case ANCR_LOOK_BEHIND:
    len = SIZE_OP_LOOK_BEHIND + tlen;
    break;
  case ANCR_LOOK_BEHIND_NOT:
    len = SIZE_OP_LOOK_BEHIND_NOT_START + tlen + SIZE_OP_LOOK_BEHIND_NOT_END;
    break;

  case ANCR_WORD_BOUNDARY:
  case ANCR_NO_WORD_BOUNDARY:
#ifdef USE_WORD_BEGIN_END
  case ANCR_WORD_BEGIN:
  case ANCR_WORD_END:
#endif
    len = SIZE_OP_WORD_BOUNDARY;
    break;

  case ANCR_TEXT_SEGMENT_BOUNDARY:
  case ANCR_NO_TEXT_SEGMENT_BOUNDARY:
    len = SIZE_OPCODE;
    break;

  default:
    len = SIZE_OPCODE;
    break;
  }

  return len;
}

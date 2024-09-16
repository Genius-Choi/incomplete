compile_anchor_node(AnchorNode* node, regex_t* reg, ScanEnv* env)
{
  int r, len;
  enum OpCode op;

  switch (node->type) {
  case ANCR_BEGIN_BUF:      r = add_op(reg, OP_BEGIN_BUF);      break;
  case ANCR_END_BUF:        r = add_op(reg, OP_END_BUF);        break;
  case ANCR_BEGIN_LINE:     r = add_op(reg, OP_BEGIN_LINE);     break;
  case ANCR_END_LINE:       r = add_op(reg, OP_END_LINE);       break;
  case ANCR_SEMI_END_BUF:   r = add_op(reg, OP_SEMI_END_BUF);   break;
  case ANCR_BEGIN_POSITION: r = add_op(reg, OP_BEGIN_POSITION); break;

  case ANCR_WORD_BOUNDARY:
    op = OP_WORD_BOUNDARY;
  word:
    r = add_op(reg, op);
    if (r != 0) return r;
    COP(reg)->word_boundary.mode = (ModeType )node->ascii_mode;
    break;

  case ANCR_NO_WORD_BOUNDARY:
    op = OP_NO_WORD_BOUNDARY; goto word;
    break;
#ifdef USE_WORD_BEGIN_END
  case ANCR_WORD_BEGIN:
    op = OP_WORD_BEGIN; goto word;
    break;
  case ANCR_WORD_END:
    op = OP_WORD_END; goto word;
    break;
#endif

  case ANCR_TEXT_SEGMENT_BOUNDARY:
  case ANCR_NO_TEXT_SEGMENT_BOUNDARY:
    {
      enum TextSegmentBoundaryType type;

      r = add_op(reg, OP_TEXT_SEGMENT_BOUNDARY);
      if (r != 0) return r;

      type = EXTENDED_GRAPHEME_CLUSTER_BOUNDARY;
#ifdef USE_UNICODE_WORD_BREAK
      if (ONIG_IS_OPTION_ON(reg->options, ONIG_OPTION_TEXT_SEGMENT_WORD))
        type = WORD_BOUNDARY;
#endif

      COP(reg)->text_segment_boundary.type = type;
      COP(reg)->text_segment_boundary.not =
        (node->type == ANCR_NO_TEXT_SEGMENT_BOUNDARY ? 1 : 0);
    }
    break;

  case ANCR_PREC_READ:
    r = add_op(reg, OP_PREC_READ_START);
    if (r != 0) return r;
    r = compile_tree(NODE_ANCHOR_BODY(node), reg, env);
    if (r != 0) return r;
    r = add_op(reg, OP_PREC_READ_END);
    break;

  case ANCR_PREC_READ_NOT:
    len = compile_length_tree(NODE_ANCHOR_BODY(node), reg);
    if (len < 0) return len;

    r = add_op(reg, OP_PREC_READ_NOT_START);
    if (r != 0) return r;
    COP(reg)->prec_read_not_start.addr = SIZE_INC_OP + len + SIZE_OP_PREC_READ_NOT_END;
    r = compile_tree(NODE_ANCHOR_BODY(node), reg, env);
    if (r != 0) return r;
    r = add_op(reg, OP_PREC_READ_NOT_END);
    break;

  case ANCR_LOOK_BEHIND:
    {
      int n;
      r = add_op(reg, OP_LOOK_BEHIND);
      if (r != 0) return r;
      if (node->char_len < 0) {
        r = get_char_len_node(NODE_ANCHOR_BODY(node), reg, &n);
        if (r != 0) return ONIGERR_INVALID_LOOK_BEHIND_PATTERN;
      }
      else
        n = node->char_len;

      COP(reg)->look_behind.len = n;
      r = compile_tree(NODE_ANCHOR_BODY(node), reg, env);
    }
    break;

  case ANCR_LOOK_BEHIND_NOT:
    {
      int n;

      len = compile_length_tree(NODE_ANCHOR_BODY(node), reg);
      r = add_op(reg, OP_LOOK_BEHIND_NOT_START);
      if (r != 0) return r;
      COP(reg)->look_behind_not_start.addr = SIZE_INC_OP + len + SIZE_OP_LOOK_BEHIND_NOT_END;

      if (node->char_len < 0) {
        r = get_char_len_node(NODE_ANCHOR_BODY(node), reg, &n);
        if (r != 0) return ONIGERR_INVALID_LOOK_BEHIND_PATTERN;
      }
      else
        n = node->char_len;

      COP(reg)->look_behind_not_start.len = n;

      r = compile_tree(NODE_ANCHOR_BODY(node), reg, env);
      if (r != 0) return r;
      r = add_op(reg, OP_LOOK_BEHIND_NOT_END);
    }
    break;

  default:
    return ONIGERR_TYPE_BUG;
    break;
  }

  return r;
}

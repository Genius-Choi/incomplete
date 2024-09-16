compile_range_repeat_node(QuantNode* qn, int target_len, int empty_info,
                          regex_t* reg, ScanEnv* env)
{
  int r;
  int num_repeat = reg->num_repeat++;

  r = add_op(reg, qn->greedy ? OP_REPEAT : OP_REPEAT_NG);
  if (r != 0) return r;

  COP(reg)->repeat.id   = num_repeat;
  COP(reg)->repeat.addr = SIZE_INC_OP + target_len + SIZE_OP_REPEAT_INC;

  r = entry_repeat_range(reg, num_repeat, qn->lower, qn->upper);
  if (r != 0) return r;

  r = compile_tree_empty_check(NODE_QUANT_BODY(qn), reg, empty_info, env);
  if (r != 0) return r;

  if (
#ifdef USE_CALL
      NODE_IS_IN_MULTI_ENTRY(qn) ||
#endif
      NODE_IS_IN_REAL_REPEAT(qn)) {
    r = add_op(reg, qn->greedy ? OP_REPEAT_INC_SG : OP_REPEAT_INC_NG_SG);
  }
  else {
    r = add_op(reg, qn->greedy ? OP_REPEAT_INC : OP_REPEAT_INC_NG);
  }
  if (r != 0) return r;

  COP(reg)->repeat_inc.id = num_repeat;
  return r;
}

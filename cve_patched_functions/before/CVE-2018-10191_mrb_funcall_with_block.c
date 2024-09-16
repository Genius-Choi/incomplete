mrb_funcall_with_block(mrb_state *mrb, mrb_value self, mrb_sym mid, mrb_int argc, const mrb_value *argv, mrb_value blk)
{
  mrb_value val;

  if (!mrb->jmp) {
    struct mrb_jmpbuf c_jmp;
    ptrdiff_t nth_ci = mrb->c->ci - mrb->c->cibase;

    MRB_TRY(&c_jmp) {
      mrb->jmp = &c_jmp;
      /* recursive call */
      val = mrb_funcall_with_block(mrb, self, mid, argc, argv, blk);
      mrb->jmp = 0;
    }
    MRB_CATCH(&c_jmp) { /* error */
      while (nth_ci < (mrb->c->ci - mrb->c->cibase)) {
        mrb->c->stack = mrb->c->ci->stackent;
        cipop(mrb);
      }
      mrb->jmp = 0;
      val = mrb_obj_value(mrb->exc);
    }
    MRB_END_EXC(&c_jmp);
    mrb->jmp = 0;
  }
  else {
    mrb_method_t m;
    struct RClass *c;
    mrb_callinfo *ci;
    int n;
    ptrdiff_t voff = -1;

    if (!mrb->c->stack) {
      stack_init(mrb);
    }
    n = mrb->c->ci->nregs;
    if (argc < 0) {
      mrb_raisef(mrb, E_ARGUMENT_ERROR, "negative argc for funcall (%S)", mrb_fixnum_value(argc));
    }
    c = mrb_class(mrb, self);
    m = mrb_method_search_vm(mrb, &c, mid);
    if (MRB_METHOD_UNDEF_P(m)) {
      mrb_sym missing = mrb_intern_lit(mrb, "method_missing");
      mrb_value args = mrb_ary_new_from_values(mrb, argc, argv);
      m = mrb_method_search_vm(mrb, &c, missing);
      if (MRB_METHOD_UNDEF_P(m)) {
        mrb_method_missing(mrb, mid, self, args);
      }
      mrb_ary_unshift(mrb, args, mrb_symbol_value(mid));
      stack_extend(mrb, n+2);
      mrb->c->stack[n+1] = args;
      argc = -1;
    }
    if (mrb->c->ci - mrb->c->cibase > MRB_FUNCALL_DEPTH_MAX) {
      mrb_exc_raise(mrb, mrb_obj_value(mrb->stack_err));
    }
    ci = cipush(mrb);
    ci->mid = mid;
    ci->stackent = mrb->c->stack;
    ci->argc = (int)argc;
    ci->target_class = c;
    mrb->c->stack = mrb->c->stack + n;
    if (mrb->c->stbase <= argv && argv < mrb->c->stend) {
      voff = argv - mrb->c->stbase;
    }
    if (MRB_METHOD_CFUNC_P(m)) {
      ci->nregs = (int)(argc + 2);
      stack_extend(mrb, ci->nregs);
    }
    else if (argc >= CALL_MAXARGS) {
      mrb_value args = mrb_ary_new_from_values(mrb, argc, argv);
      stack_extend(mrb, ci->nregs+2);
      mrb->c->stack[1] = args;
      ci->argc = -1;
      argc = 1;
    }
    else {
      struct RProc *p = MRB_METHOD_PROC(m);
      ci->proc = p;
      if (argc < 0) argc = 1;
      ci->nregs = (int)(p->body.irep->nregs + argc);
      stack_extend(mrb, ci->nregs);
    }
    if (voff >= 0) {
      argv = mrb->c->stbase + voff;
    }
    mrb->c->stack[0] = self;
    if (ci->argc > 0) {
      stack_copy(mrb->c->stack+1, argv, argc);
    }
    mrb->c->stack[argc+1] = blk;

    if (MRB_METHOD_CFUNC_P(m)) {
      int ai = mrb_gc_arena_save(mrb);

      ci->acc = CI_ACC_DIRECT;
      if (MRB_METHOD_PROC_P(m)) {
        ci->proc = MRB_METHOD_PROC(m);
      }
      val = MRB_METHOD_CFUNC(m)(mrb, self);
      mrb->c->stack = mrb->c->ci->stackent;
      cipop(mrb);
      mrb_gc_arena_restore(mrb, ai);
    }
    else {
      ci->acc = CI_ACC_SKIP;
      val = mrb_run(mrb, MRB_METHOD_PROC(m), self);
    }
  }
  mrb_gc_protect(mrb, val);
  return val;
}

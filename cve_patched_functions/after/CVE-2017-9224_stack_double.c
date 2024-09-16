stack_double(int is_alloca, char** arg_alloc_base,
	     OnigStackType** arg_stk_base,
	     OnigStackType** arg_stk_end, OnigStackType** arg_stk,
	     OnigMatchArg* msa)
{
  unsigned int n;
  int used;
  size_t size;
  size_t new_size;
  char* alloc_base;
  char* new_alloc_base;
  OnigStackType *stk_base, *stk_end, *stk;

  alloc_base = *arg_alloc_base;
  stk_base = *arg_stk_base;
  stk_end  = *arg_stk_end;
  stk      = *arg_stk;

  n = stk_end - stk_base;
  size = sizeof(OnigStackIndex) * msa->ptr_num + sizeof(OnigStackType) * n;
  n *= 2;
  new_size = sizeof(OnigStackIndex) * msa->ptr_num + sizeof(OnigStackType) * n;
  if (is_alloca != 0) {
    new_alloc_base = (char* )xmalloc(new_size);
    if (IS_NULL(new_alloc_base)) {
      STACK_SAVE;
      return ONIGERR_MEMORY;
    }
    xmemcpy(new_alloc_base, alloc_base, size);
  }
  else {
    if (MatchStackLimitSize != 0 && n > MatchStackLimitSize) {
      if ((unsigned int )(stk_end - stk_base) == MatchStackLimitSize)
        return ONIGERR_MATCH_STACK_LIMIT_OVER;
      else
        n = MatchStackLimitSize;
    }
    new_alloc_base = (char* )xrealloc(alloc_base, new_size);
    if (IS_NULL(new_alloc_base)) {
      STACK_SAVE;
      return ONIGERR_MEMORY;
    }
  }

  alloc_base = new_alloc_base;
  used = stk - stk_base;
  *arg_alloc_base = alloc_base;
  *arg_stk_base   = (OnigStackType* )(alloc_base
		       + (sizeof(OnigStackIndex) * msa->ptr_num));
  *arg_stk      = *arg_stk_base + used;
  *arg_stk_end  = *arg_stk_base + n;
  return 0;
}

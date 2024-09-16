clear_opt_exact(OptStr* e)
{
  clear_mml(&e->mmd);
  clear_opt_anc_info(&e->anc);
  e->reach_end      = 0;
  e->case_fold      = 0;
  e->good_case_fold = 0;
  e->len            = 0;
  e->s[0]           = '\0';
}

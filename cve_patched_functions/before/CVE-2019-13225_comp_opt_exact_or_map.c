comp_opt_exact_or_map(OptStr* e, OptMap* m)
{
#define COMP_EM_BASE  20
  int ae, am;
  int case_value;

  if (m->value <= 0) return -1;

  if (e->case_fold != 0) {
    if (e->good_case_fold != 0)
      case_value = 2;
    else
      case_value = 1;
  }
  else
    case_value = 3;

  ae = COMP_EM_BASE * e->len * case_value;
  am = COMP_EM_BASE * 5 * 2 / m->value;
  return comp_distance_value(&e->mmd, &m->mmd, ae, am);
}

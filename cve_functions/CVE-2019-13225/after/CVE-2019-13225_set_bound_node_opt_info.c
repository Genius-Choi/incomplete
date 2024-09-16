set_bound_node_opt_info(OptNode* opt, MinMax* plen)
{
  copy_mml(&(opt->sb.mmd),  plen);
  copy_mml(&(opt->spr.mmd), plen);
  copy_mml(&(opt->map.mmd), plen);
}

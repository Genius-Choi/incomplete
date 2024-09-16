static void update_h_load(long cpu)
{
	walk_tg_tree(tg_load_down, tg_nop, (void *)cpu);
}

trigger_set_xy(int trigger_index, int x, int y)
{
	struct map_trigger* trigger;

	trigger = vector_get(s_map->triggers, trigger_index);
	trigger->x = x;
	trigger->y = y;
}

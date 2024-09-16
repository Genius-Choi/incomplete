trigger_set_layer(int trigger_index, int layer)
{
	struct map_trigger* trigger;

	trigger = vector_get(s_map->triggers, trigger_index);
	trigger->z = layer;
}

map_engine_on_update(script_t* script)
{
	script_unref(s_update_script);
	s_update_script = script_ref(script);
}

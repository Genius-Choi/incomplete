cleanup_process_schemap (runtime_spec_schema_config_schema_process **p)
{
  runtime_spec_schema_config_schema_process *process = *p;
  if (process)
    (void) free_runtime_spec_schema_config_schema_process (process);
}

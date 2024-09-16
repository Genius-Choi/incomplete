raptor_nspace_compare(const void *a, const void *b)
{
  raptor_namespace* ns_a=*(raptor_namespace**)a;
  raptor_namespace* ns_b=*(raptor_namespace**)b;
  if(!ns_a->prefix)
    return 1;
  else if(!ns_b->prefix)
    return -1;
  else
    return strcmp((const char*)ns_b->prefix, (const char*)ns_a->prefix);
}

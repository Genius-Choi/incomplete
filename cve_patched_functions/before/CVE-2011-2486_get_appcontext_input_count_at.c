static inline int get_appcontext_input_count_at(int offset)
{
  return *((short *)((char *)x_app_context + offset));
}

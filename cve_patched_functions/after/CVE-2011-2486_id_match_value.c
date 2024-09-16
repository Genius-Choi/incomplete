static gboolean id_match_value(gpointer key, gpointer value, gpointer user_data)
{
  if (value == *(gpointer *)user_data) {
	*(int *)user_data = (uintptr_t)key;
	return true;
  }
  return false;
}

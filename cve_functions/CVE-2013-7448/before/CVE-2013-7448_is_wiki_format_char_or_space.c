is_wiki_format_char_or_space(char c)
{
  if (isspace(c)) return 1;
  if (strchr("/*_-", c)) return 1; 
  return 0;
}

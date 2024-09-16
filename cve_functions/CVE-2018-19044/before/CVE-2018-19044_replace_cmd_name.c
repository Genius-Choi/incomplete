replace_cmd_name(notify_script_t *script, char *new_path)
{
	size_t len;
	char **wp = &script->args[1];
	size_t num_words = 1;
	char **params;
	char **word_ptrs;
	char *words;

	len = strlen(new_path) + 1;
	while (*wp)
		len += strlen(*wp++) + 1;
	num_words = ((char **)script->args[0] - &script->args[0]) - 1;

	params = word_ptrs = MALLOC((num_words + 1) * sizeof(char *) + len);
	words = (char *)&params[num_words + 1];

	strcpy(words, new_path);
	*(word_ptrs++) = words;
	words += strlen(words) + 1;

	wp = &script->args[1];
	while (*wp) {
		strcpy(words, *wp);
		*(word_ptrs++) = words;
		words += strlen(*wp) + 1;
		wp++;
	}
	*word_ptrs = NULL;

	FREE(script->args);
	script->args = params;
}

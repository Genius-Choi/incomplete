simil(const char *str1, const char *str2)
{
	LINK1 top = NULL;
	unsigned int score = 0;
	size_t common, total;
	size_t len1, len2;
	char *rs1 = NULL, *rs2 = NULL;
	char *s1, *s2;
	char ls1[MAX_PATTERN_SIZ], ls2[MAX_PATTERN_SIZ];

	if(strcasecmp(str1, str2) == 0)
		return 100;

	if((s1 = cli_strdup(str1)) == NULL)
		return OUT_OF_MEMORY;
	if((s2 = cli_strdup(str2)) == NULL) {
		free(s1);
		return OUT_OF_MEMORY;
	}

	if(((total = strstrip(s1)) > MAX_PATTERN_SIZ - 1) || ((len2 = strstrip(s2)) > MAX_PATTERN_SIZ - 1)) {
		free(s1);
		free(s2);
		return ARRAY_OVERFLOW;
	}

	total += len2;

	if((push(&top, s1) == OUT_OF_MEMORY) ||
	   (push(&top, s2) == OUT_OF_MEMORY)) {
		free(s1);
		free(s2);
		return OUT_OF_MEMORY;
	}

	while(pop(&top, ls2) == SUCCESS) {
		pop(&top, ls1);
		common = compare(ls1, &rs1, ls2, &rs2);
		if(common > 0) {
			score += (unsigned int)common;
			len1 = strlen(ls1);
			len2 = strlen(ls2);

			if((len1 > 1 && len2 >= 1) || (len2 > 1 && len1 >= 1))
				if((push(&top, ls1) == OUT_OF_MEMORY) || (push(&top, ls2) == OUT_OF_MEMORY)) {
					free(s1);
					free(s2);
					return OUT_OF_MEMORY;
				}
			len1 = strlen(rs1);
			len2 = strlen(rs2);

			if((len1 > 1 && len2 >= 1) || (len2 > 1 && len1 >= 1))
				if((push(&top, rs1) == OUT_OF_MEMORY) || (push(&top, rs2) == OUT_OF_MEMORY)) {
					free(s1);
					free(s2);
					return OUT_OF_MEMORY;
				}
		}
	}
	free(s1);
	free(s2);
	return (total > 0) ? ((score * 200) / total) : 0;
}

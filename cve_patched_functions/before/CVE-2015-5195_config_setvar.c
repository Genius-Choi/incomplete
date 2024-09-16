config_setvar(
	config_tree *ptree
	)
{
	setvar_node *my_node;
	size_t	varlen, vallen, octets;
	char *	str;

	str = NULL;
	my_node = HEAD_PFIFO(ptree->setvar);
	for (; my_node != NULL; my_node = my_node->link) {
		varlen = strlen(my_node->var);
		vallen = strlen(my_node->val);
		octets = varlen + vallen + 1 + 1;
		str = erealloc(str, octets);
		snprintf(str, octets, "%s=%s", my_node->var,
			 my_node->val);
		set_sys_var(str, octets, (my_node->isdefault)
						? DEF 
						: 0);
	}
	if (str != NULL)
		free(str);
}

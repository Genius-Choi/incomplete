static void free_Var(Var* var) {
	if (var) {
		free (var->szKey);
		free (var->Value);
		free (var);
	}
}

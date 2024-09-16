runtest(int i) {
    int ret = 0, res;
    int old_errors, old_tests, old_leaks;

    old_errors = nb_errors;
    old_tests = nb_tests;
    old_leaks = nb_leaks;
    if ((tests_quiet == 0) && (testDescriptions[i].desc != NULL))
	printf("## %s\n", testDescriptions[i].desc);
    res = launchTests(&testDescriptions[i]);
    if (res != 0)
	ret++;
    if (verbose) {
	if ((nb_errors == old_errors) && (nb_leaks == old_leaks))
	    printf("Ran %d tests, no errors\n", nb_tests - old_tests);
	else
	    printf("Ran %d tests, %d errors, %d leaks\n",
		   nb_tests - old_tests,
		   nb_errors - old_errors,
		   nb_leaks - old_leaks);
    }
    return(ret);
}

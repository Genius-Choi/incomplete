static void test_conf_files_list(bool use_root) {
        char tmp_dir[] = "/tmp/test-conf-files-XXXXXX";
        _cleanup_strv_free_ char **found_files = NULL;
        const char *root_dir, *search_1, *search_2, *expect_a, *expect_b;

        setup_test_dir(tmp_dir,
                       "/dir1/a.conf",
                       "/dir2/a.conf",
                       "/dir2/b.conf",
                       NULL);

        if (use_root) {
                root_dir = tmp_dir;
                search_1 = "/dir1";
                search_2 = "/dir2";
        } else {
                root_dir = NULL;
                search_1 = strjoina(tmp_dir, "/dir1");
                search_2 = strjoina(tmp_dir, "/dir2");
        }

        expect_a = strjoina(tmp_dir, "/dir1/a.conf");
        expect_b = strjoina(tmp_dir, "/dir2/b.conf");

        assert_se(conf_files_list(&found_files, ".conf", root_dir, search_1, search_2, NULL) == 0);
        strv_print(found_files);

        assert_se(found_files);
        assert_se(streq_ptr(found_files[0], expect_a));
        assert_se(streq_ptr(found_files[1], expect_b));
        assert_se(found_files[2] == NULL);

        assert_se(rm_rf(tmp_dir, REMOVE_ROOT|REMOVE_PHYSICAL) == 0);
}

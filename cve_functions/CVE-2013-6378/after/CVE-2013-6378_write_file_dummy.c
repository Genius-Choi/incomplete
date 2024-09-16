static ssize_t write_file_dummy(struct file *file, const char __user *buf,
                                size_t count, loff_t *ppos)
{
        return -EINVAL;
}

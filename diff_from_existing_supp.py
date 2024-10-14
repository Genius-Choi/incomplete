import os
import difflib

# Path to the base directory where CVE folders are located
base_dir = './EXISTING_SUPP/'

def compare_files(before_file, after_file):
    """Compare two files and return the differences."""
    with open(before_file, 'r') as f_before, open(after_file, 'r') as f_after:
        before_lines = f_before.readlines()
        after_lines = f_after.readlines()

        # Use difflib to get the differences
        diff = difflib.unified_diff(before_lines, after_lines, 
                                    fromfile='before', tofile='after', 
                                    lineterm='')
        return list(diff)

def compare_patched_files(cve_id):
    """Compare files in the before and after folders of the given CVE folder."""
    patched_path = os.path.join(base_dir, cve_id, 'patched')
    before_dir = os.path.join(patched_path, 'before')
    after_dir = os.path.join(patched_path, 'after')

    if not os.path.exists(before_dir) or not os.path.exists(after_dir):
        print(f"Missing before or after directory in {cve_id}")
        return

    # List files in both directories
    before_files = {f for f in os.listdir(before_dir) if os.path.isfile(os.path.join(before_dir, f))}
    after_files = {f for f in os.listdir(after_dir) if os.path.isfile(os.path.join(after_dir, f))}

    # Find matching files by name
    common_files = before_files.intersection(after_files)

    for file_name in common_files:
        before_file = os.path.join(before_dir, file_name)
        after_file = os.path.join(after_dir, file_name)

        # Get the differences between the files
        differences = compare_files(before_file, after_file)
        
        if differences:
            print(f"Differences for {file_name} in {cve_id}:")
            for line in differences:
                print(line)
        else:
            print(f"No differences found for {file_name} in {cve_id}")

# Iterate over all CVE folders
for cve_id in os.listdir(base_dir):
    cve_path = os.path.join(base_dir, cve_id)
    if os.path.isdir(cve_path):
        compare_patched_files(cve_id)

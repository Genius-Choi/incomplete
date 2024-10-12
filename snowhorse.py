import os

directory = './new_cve_code_changes'

allowed_extensions = ('.c', '.cpp', '.cc', '.php', '.py', '.java', '.rb')

for root, dirs, files in os.walk(directory):
    for file in files:
        if not file.endswith(allowed_extensions):
            print(os.path.join(root, file))

import subprocess
import json
import os
import re
import difflib

missing_end_line_count = 0

def compare_before_after_files(before_path, after_path):
    with open(before_path, 'r') as before_file, open(after_path, 'r') as after_file:
        before_lines = before_file.readlines()
        after_lines = after_file.readlines()

    differ = difflib.Differ()
    diff = list(differ.compare(before_lines, after_lines))

    deleted_lines = []
    for i, line in enumerate(diff):
        if line.startswith('- '):
            deleted_lines.append(i + 1)  # +1 because line numbers start at 1

    return deleted_lines

def process_patched_functions():
    before_dir = './cve_patched_functions/before'
    after_dir = './cve_patched_functions/after'
    results = {}

    for filename in os.listdir(before_dir):
        before_path = os.path.join(before_dir, filename)
        after_path = os.path.join(after_dir, filename)

        if os.path.isfile(after_path):
            deleted_lines = compare_before_after_files(before_path, after_path)
            if deleted_lines:
                results[filename] = deleted_lines

    return results

def get_file_extension(file_path):
    _, extension = os.path.splitext(file_path)
    return extension

def sanitize_filename(filename, max_length=200):
    # Remove or replace characters that are invalid in file names
    filename = re.sub(r'[<>:"/\\|?*]', '_', filename)
    filename = filename.replace(' ', '_')
    # Truncate if too long
    # if len(filename) > max_length:
    #     filename = filename[:max_length]
    return filename

def run_ctags(file_path):
    try:
        result = subprocess.run(['ctags', '--fields=+ne', '-o', '-', '--sort=no', file_path],
                                capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        print(f"Error running ctags on {file_path}: {e}")
        return None

def parse_ctags_output(ctags_output, file_path):
    functions = []
    for line in ctags_output.split('\n'):
        if line.strip():
            parts = line.split('\t')
            if len(parts) >= 4 and 'f' in parts[3]:  # Only function
                func_info = {
                    'name': parts[0],
                    'file': parts[1],
                    'sig': parts[2].strip('/^').strip('$/'),
                }
                for field in parts[4:]:
                    if field.startswith('line:'):
                        func_info['start_line'] = int(field.split(':')[1])
                    elif field.startswith('end:'):
                        func_info['end_line'] = int(field.split(':')[1])
                functions.append(func_info)
    return functions

def get_functions_from_file(file_path):
    global missing_end_line_count
    functions = []
    ctags_output = run_ctags(file_path)
    if ctags_output:
        functions = parse_ctags_output(ctags_output, file_path)
        # Sort functions by start_line
        functions.sort(key=lambda x: x['start_line'])
        # Fill in missing end_line
        for i, func in enumerate(functions):
            if 'end_line' not in func:
                missing_end_line_count += 1
                if i < len(functions) - 1:
                    func['end_line'] = functions[i+1]['start_line'] - 2
                else:
                    # For the last function without end_line, use the file's total lines
                    with open(file_path, 'r') as f:
                        func['end_line'] = sum(1 for _ in f)
    return functions

def extract_function_code(file_path, start_line, end_line):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        return ''.join(lines[start_line-1:end_line])

def save_function_code(cve_id, function_name, code, state, file_extension):
    directory = os.path.join('cve_patched_functions', state)
    os.makedirs(directory, exist_ok=True)
    
    sanitized_function_name = sanitize_filename(function_name)
    file_name = f"{cve_id}_{sanitized_function_name}{file_extension}"
    file_path = os.path.join(directory, file_name)
    
    with open(file_path, 'w') as file:
        file.write(code)

def parse_diff(diff_file):
    changed_lines = {'before': [], 'after': []}
    current_file = None
    with open(diff_file, 'r') as f:
        for line in f:
            if line.startswith('diff --git'):
                current_file = line.split()[-1][2:]
            elif line.startswith('@@'):
                match = re.match(r'@@ -(\d+),(\d+) \+(\d+),(\d+) @@', line)
                if match:
                    before_start, before_len, after_start, after_len = map(int, match.groups())
                    before_end = before_start + before_len
                    after_end = after_start + after_len
                    changed_lines['before'].extend(range(before_start, before_end))
                    changed_lines['after'].extend(range(after_start, after_end))
    return changed_lines


def process_cve_folder(cve_folder, diff_file):
    changed_lines = parse_diff(diff_file)
    results = {'before': {}, 'after': {}}
    
    for state in ['before', 'after']:
        state_dir = os.path.join(cve_folder, state)
        for file_name in os.listdir(state_dir):
            file_path = os.path.join(state_dir, file_name)
            if os.path.isfile(file_path):
                file_extension = get_file_extension(file_path)
                functions = get_functions_from_file(file_path)
                if functions:
                    results[state][file_name] = []
                    cve_id = os.path.basename(cve_folder)
                    for func in functions:
                        if any(line in changed_lines[state] for line in range(func['start_line'], func['end_line'] + 1)):
                            results[state][file_name].append(func)
                            function_code = extract_function_code(
                                file_path, 
                                func['start_line'], 
                                func['end_line']
                            )
                            save_function_code(
                                cve_id, 
                                func['name'], 
                                function_code, 
                                state,
                                file_extension
                            )
    return results

def main():
    root_folder = 'cve_code_changes'
    diff_folder = 'cve_diffs'
    all_results = {}
    
    for cve_folder in os.listdir(root_folder):
        cve_path = os.path.join(root_folder, cve_folder)
        diff_file = os.path.join(diff_folder, cve_folder, 'commit_1.diff')
        if os.path.isdir(cve_path) and os.path.isfile(diff_file):
            print(f"Processing {cve_folder}...")
            all_results[cve_folder] = process_cve_folder(cve_path, diff_file)

    with open('cve_patched_functions_analysis.json', 'w') as f:
        json.dump(all_results, f, indent=2)

    print("Analysis complete. Results saved to 'cve_patched_functions_analysis.json'")
    print("Patched function code files saved in 'cve_patched_functions/before' and 'cve_patched_functions/after' directories")
    print(f"Missing endline field: {missing_end_line_count}")


    print("Analyzing patched functions...")
    patched_function_results = process_patched_functions()
    with open('../json_data/patched_line_num.json', 'w') as f:
        json.dump(patched_function_results, f, indent=2)

    print("Patched function analysis complete. Results saved to '../json_data/patched_line_num.json'")

if __name__ == "__main__":
    main()
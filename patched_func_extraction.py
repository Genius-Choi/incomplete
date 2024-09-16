# Considering 4373 CVEs, 615567 functions
# 307473 patched functions (before)
# 308094 patched functions (after)
# 912 functions do not have "end_line" field -> 다음 함수의 시작줄 -2 로 대체

import subprocess
import json
import os
import re

# Global counter for missing end_line cases
missing_end_line_count = 0
ctags_returns_none = 0

def sanitize_filename(filename):
    # Remove or replace characters that are invalid in file names
    filename = re.sub(r'[<>:"/\\|?*]', '_', filename)
    filename = filename.replace(' ', '_')
    return filename

def run_ctags(file_path):
    try:
        result = subprocess.run(['ctags', '--fields=+ne', '-o', '-', '--sort=no', file_path],
                                capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        print(f"Error running ctags on {file_path}: {e}")
        ctags_returns_none += 1
        return ""  # Return empty string instead of None

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

# def get_functions_from_file(file_path):
#     global missing_end_line_count
#     ctags_output = run_ctags(file_path)
#     if ctags_output:
#         functions = parse_ctags_output(ctags_output, file_path)
#         # Sort functions by start_line
#         functions.sort(key=lambda x: x['start_line'])
#         # Fill in missing end_line
#         for i, func in enumerate(functions):
#             if 'end_line' not in func:
#                 missing_end_line_count += 1
#                 if i < len(functions) - 1:
#                     func['end_line'] = functions[i+1]['start_line'] - 2
#                 else:
#                     # For the last function, use the file's total lines
#                     with open(file_path, 'r') as f:
#                         func['end_line'] = sum(1 for _ in f)
#     return functions

def get_functions_from_file(file_path):
    global missing_end_line_count
    functions = []  # Initialize functions list here
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
        total_lines = len(lines)
        end_line = min(end_line, total_lines)  # Ensure end_line doesn't exceed file length
        return ''.join(lines[start_line-1:end_line])

# def save_function_code(cve_id, function_name, code, state):
#     directory = os.path.join('cve_patched_functions', state)
#     os.makedirs(directory, exist_ok=True)
    
#     file_name = f"{cve_id}_{function_name}.c"
#     file_path = os.path.join(directory, file_name)
    
#     with open(file_path, 'w') as file:
#         file.write(code)

def save_function_code(cve_id, function_name, code, state):
    directory = os.path.join('cve_patched_functions', state)
    os.makedirs(directory, exist_ok=True)
    
    sanitized_function_name = sanitize_filename(function_name)
    file_name = f"{cve_id}_{sanitized_function_name}.c"
    file_path = os.path.join(directory, file_name)
    
    with open(file_path, 'w') as file:
        file.write(code)

def process_cve_folder(cve_folder):
    results = {'before': {}, 'after': {}}
    for state in ['before', 'after']:
        state_dir = os.path.join(cve_folder, state)
        for file_name in os.listdir(state_dir):
            file_path = os.path.join(state_dir, file_name)
            if os.path.isfile(file_path):
                functions = get_functions_from_file(file_path)
                if functions:
                    results[state][file_name] = functions
                    
                    cve_id = os.path.basename(cve_folder)
                    for func in functions:
                        function_code = extract_function_code(
                            file_path, 
                            func['start_line'], 
                            func['end_line']
                        )
                        save_function_code(
                            cve_id, 
                            func['name'], 
                            function_code, 
                            state
                        )
    return results

def main():
    global missing_end_line_count
    root_folder = 'cve_code_changes'
    all_results = {}
    
    for cve_folder in os.listdir(root_folder):
        cve_path = os.path.join(root_folder, cve_folder)
        if os.path.isdir(cve_path):
            print(f"Processing {cve_folder}...")
            all_results[cve_folder] = process_cve_folder(cve_path)

    with open('../json_data/cve_patched_functions_analysis.json', 'w') as f:
        json.dump(all_results, f, indent=2)

    print("Analysis complete. Results saved to '../json_data/cve_patched_functions_analysis.json'")
    print("Patched function code files saved in 'cve_patched_functions' directory")
    print(f"Number of functions with missing end_line: {missing_end_line_count}")
    print(f"Number of functions which ctags returns none: {ctags_returns_none}")
    

if __name__ == "__main__":
    main()
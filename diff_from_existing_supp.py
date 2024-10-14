import os
import difflib

# CVE 폴더가 있는 기본 경로 설정
base_dir = './existing_supp/'

def compare_files(before_file, after_file):
    """두 파일을 비교하고 diff 결과를 반환."""
    with open(before_file, 'r') as f_before, open(after_file, 'r') as f_after:
        before_lines = f_before.readlines()
        after_lines = f_after.readlines()

        # difflib을 사용하여 차이점 추출
        diff = difflib.unified_diff(before_lines, after_lines, 
                                    fromfile='before', tofile='after', 
                                    lineterm='')
        return list(diff)

def save_diff_to_file(diff_lines, output_file):
    """diff 결과를 파일로 저장."""
    with open(output_file, 'w') as f_out:
        for line in diff_lines:
            f_out.write(line + '\n')

def compare_patched_files(cve_id):
    """주어진 CVE 폴더의 before와 after 폴더의 파일을 비교하고 diff 폴더에 결과 저장."""
    patched_path = os.path.join(base_dir, cve_id, 'patched')
    before_dir = os.path.join(patched_path, 'before')
    after_dir = os.path.join(patched_path, 'after')
    diff_dir = os.path.join(base_dir, cve_id, 'diff')

    if not os.path.exists(before_dir) or not os.path.exists(after_dir):
        print(f"{cve_id}에 before 또는 after 디렉토리가 없습니다.")
        return

    # diff 디렉토리가 없으면 생성
    os.makedirs(diff_dir, exist_ok=True)

    # before와 after 디렉토리의 파일 목록 가져오기
    before_files = {f for f in os.listdir(before_dir) if os.path.isfile(os.path.join(before_dir, f))}
    after_files = {f for f in os.listdir(after_dir) if os.path.isfile(os.path.join(after_dir, f))}

    # 파일 이름이 같은 것만 비교
    common_files = before_files.intersection(after_files)

    for file_name in common_files:
        before_file = os.path.join(before_dir, file_name)
        after_file = os.path.join(after_dir, file_name)

        # 파일 간 차이점 추출
        differences = compare_files(before_file, after_file)
        
        if differences:
            # diff 결과 파일 경로 설정
            diff_file = os.path.join(diff_dir, f"{file_name}.diff")
            save_diff_to_file(differences, diff_file)
            print(f"{file_name}의 차이점을 {diff_file}에 저장했습니다.")
        else:
            print(f"{file_name}에 차이점이 없습니다.")

# CVE 폴더를 순회하면서 diff 생성
for cve_id in os.listdir(base_dir):
    cve_path = os.path.join(base_dir, cve_id)
    if os.path.isdir(cve_path):
        compare_patched_files(cve_id)

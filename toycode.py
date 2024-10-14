import os

# CVE 폴더가 있는 기본 경로 설정
base_dir = './existing_supp/'

def find_empty_dep_folders():
    """dep 폴더가 비어 있는 CVE-id 폴더를 찾아 출력하고, 총 개수를 반환."""
    empty_dep_cve_ids = []

    # CVE 폴더 순회
    for cve_id in os.listdir(base_dir):
        cve_path = os.path.join(base_dir, cve_id)
        
        # CVE 폴더 안에 dep 폴더가 있는지 확인
        dep_path = os.path.join(cve_path, 'dep')
        if os.path.isdir(dep_path):
            # dep 폴더가 비어있는지 확인
            if not os.listdir(dep_path):  # 폴더가 비어 있으면
                empty_dep_cve_ids.append(cve_id)

    # 결과 출력
    print(f"dep 폴더가 비어 있는 CVE-id: {empty_dep_cve_ids}")
    print(f"총 {len(empty_dep_cve_ids)}개의 CVE-id에서 dep 폴더가 비어 있습니다.")

# 함수 실행
find_empty_dep_folders()

import os
import shutil
import json
from urllib.parse import urlparse

# 지원하는 확장자 목록
SUPPORTED_EXTENSIONS = {'.c', '.cpp', '.cc', '.php', '.py', '.java', '.rb'}

def get_file_extension(file_path):
    return os.path.splitext(file_path)[1]

def should_delete_repo(commit_data):
    """
    해당 커밋 데이터에서 지원하는 확장자를 가진 파일이 없으면 True를 반환.
    """
    for commit in commit_data:
        for file_change in commit['index_commits']:
            file_extension = get_file_extension(file_change['file'])
            if file_extension in SUPPORTED_EXTENSIONS:
                return False  # 지원하는 확장자를 가진 파일이 있으면 삭제하지 않음
    return True

def get_repo_name_from_url(repo_url):
    """
    GitHub 리포지토리 URL에서 리포지토리 이름을 추출.
    """
    return os.path.basename(urlparse(repo_url).path)

def delete_repo_if_needed(cve_data, cloned_repos_dir):
    for cve, commit_data in cve_data.items():
        for commit in commit_data:
            repo_url = commit['commit_url']
            repo_name = get_repo_name_from_url(repo_url)
            repo_path = os.path.join(cloned_repos_dir, repo_name)
            
            if os.path.exists(repo_path):
                if should_delete_repo(commit_data):
                    print(f"{repo_name} 리포지토리를 삭제합니다...")
                    shutil.rmtree(repo_path)  # 리포지토리 삭제
                else:
                    print(f"{repo_name} 리포지토리는 삭제하지 않습니다.")

def main():
    # cpp_index_commits.json 파일 로드
    with open('cpp_index_commits.json', 'r') as f:
        cve_data = json.load(f)

    cloned_repos_dir = '../clonedhere'  # 클론된 리포지토리들이 있는 디렉토리

    delete_repo_if_needed(cve_data, cloned_repos_dir)
    
    print("필요한 리포지토리 삭제가 완료되었습니다.")

if __name__ == "__main__":
    main()

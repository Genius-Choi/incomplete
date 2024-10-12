# import json
# import os
# import requests
# import time

# def load_cpp_index_commits(file_path):
#     with open(file_path, 'r') as f:
#         return json.load(f)

# def create_directory(path):
#     if not os.path.exists(path):
#         os.makedirs(path)

# def download_diff(url, save_path):
#     response = requests.get(url)
#     if response.status_code == 200:
#         with open(save_path, 'w', encoding='utf-8') as f:
#             f.write(response.text)
#         print(f"Downloaded: {url}")
#     else:
#         print(f"Failed to download: {url}")

# def process_cves(data):
#     base_dir = "./cve_diffs"
#     create_directory(base_dir)

#     for cve_id, commits in data.items():
#         cve_dir = os.path.join(base_dir, cve_id)
#         create_directory(cve_dir)

#         for i, commit in enumerate(commits):
#             diff_url = commit['commit_url'] + '.diff'
#             file_name = f"commit_{i+1}.diff"
#             save_path = os.path.join(cve_dir, file_name)

#             # 이미 파일이 존재하는지 확인
#             if os.path.exists(save_path):
#                 print(f"File already exists, skipping: {save_path}")
#                 continue  # 파일이 이미 있으면 건너뜀

#             download_diff(diff_url, save_path)
#             time.sleep(0.5)  # 서버에 부담을 주지 않기 위해 잠시 대기

# def main():
#     data = load_cpp_index_commits('cpp_index_commits.json')
#     process_cves(data)

# if __name__ == "__main__":
#     main()


import json
import os
import requests
import time

def load_cpp_index_commits(file_path):
    with open(file_path, 'r') as f:
        return json.load(f)

def create_directory(path):
    if not os.path.exists(path):
        os.makedirs(path)

def download_diff(url, save_path):
    try:
        response = requests.get(url)
        response.raise_for_status()  # Raises HTTPError for bad responses
        with open(save_path, 'w', encoding='utf-8') as f:
            f.write(response.text)
        print(f"Downloaded: {url}")
    except requests.exceptions.RequestException as e:
        print(f"Failed to download {url}: {e}")

def process_cves(data):
    check_dir = "./cve_diffs"       # Directory to check existing diffs
    save_dir = "./cve_diffs2"       # Directory to save new diffs
    create_directory(save_dir)

    for cve_id, commits in data.items():
        cve_check_path = os.path.join(check_dir, cve_id)
        cve_save_path = os.path.join(save_dir, cve_id)
        create_directory(cve_save_path)

        for i, commit in enumerate(commits):
            diff_url = commit['commit_url'] + '.diff'
            file_name = f"commit_{i+1}.diff"
            
            # Path to check if the diff already exists
            existing_file_path = os.path.join(cve_check_path, file_name)
            
            # Path to save the new diff
            save_file_path = os.path.join(cve_save_path, file_name)

            # Check if the diff exists in the check_dir
            if os.path.exists(existing_file_path):
                print(f"File already exists in {check_dir}, skipping: {existing_file_path}")
                continue  # Skip downloading if it exists

            # Optionally, also check if it exists in save_dir to avoid duplicates there
            if os.path.exists(save_file_path):
                print(f"File already exists in {save_dir}, skipping: {save_file_path}")
                continue

            download_diff(diff_url, save_file_path)
            time.sleep(0.5)  # Pause to avoid overwhelming the server

def main():
    data = load_cpp_index_commits('cpp_index_commits.json')
    process_cves(data)

if __name__ == "__main__":
    main()

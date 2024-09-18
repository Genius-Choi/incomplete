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
    response = requests.get(url)
    if response.status_code == 200:
        with open(save_path, 'w', encoding='utf-8') as f:
            f.write(response.text)
        print(f"Downloaded: {url}")
    else:
        print(f"Failed to download: {url}")

def process_cves(data):
    base_dir = "./cve_diffs"
    create_directory(base_dir)

    for cve_id, commits in data.items():
        cve_dir = os.path.join(base_dir, cve_id)
        create_directory(cve_dir)

        for i, commit in enumerate(commits):
            diff_url = commit['commit_url'] + '.diff'
            file_name = f"commit_{i+1}.diff"
            save_path = os.path.join(cve_dir, file_name)
            
            download_diff(diff_url, save_path)
            time.sleep(0.5)  # To avoid overwhelming the server

def main():
    data = load_cpp_index_commits('cpp_index_commits.json')
    process_cves(data)

if __name__ == "__main__":
    main()
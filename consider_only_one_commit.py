import os
import shutil

def clean_cve_folders(base_path):
    deleted_count = 0
    
    for folder_name in os.listdir(base_path):
        folder_path = os.path.join(base_path, folder_name)
        
        if os.path.isdir(folder_path):
            diff_files = [f for f in os.listdir(folder_path) if f.endswith('.diff')]
            
            if len(diff_files) > 1:
                shutil.rmtree(folder_path)
                print(f"Deleted folder: {folder_name}")
                deleted_count += 1
    
    return deleted_count

def main():
    base_path = "./cve_diffs"
    
    if not os.path.exists(base_path):
        print(f"Error: {base_path} does not exist.")
        return
    
    deleted_folders = clean_cve_folders(base_path)
    print(f"Total folders deleted: {deleted_folders}")

if __name__ == "__main__":
    main()
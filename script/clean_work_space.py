import os
import shutil
import argparse

def delete_cmake_dirs(root_dir):
    for dirpath, dir_names, _ in os.walk(root_dir):
        # Copy the current directory name list to avoid problems caused by modifying during traversal
        for dirname in dir_names[:]:
            if 'cmake-build-debug' in dirname:
                full_path = os.path.join(dirpath, dirname)
                print(f"Deleting {full_path}...")
                try:
                    shutil.rmtree(full_path)
                    print(f"Successfully deleted {full_path}")
                except Exception as e:
                    print(f"Failed to delete {full_path}: {e}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Delete all directories containing "cmake-build-debug" in their names.')
    parser.add_argument('--path', default='..', help='Root directory to start deletion (default: current directory)')
    args = parser.parse_args()

    print(f"Starting deletion from: {args.path}")
    delete_cmake_dirs(args.path)
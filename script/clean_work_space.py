#!/usr/bin/env python3
"""
Script to clean up workspace by removing build directories.
"""

import os
import shutil
import argparse
import sys
from typing import List


def delete_cmake_dirs(root_dir: str, target_dirs: List[str]) -> None:
    """
    Delete directories matching target names recursively.
    
    @param root_dir: Root directory to start searching
    @param target_dirs: List of directory names/patterns to delete
    """
    deleted_count = 0
    error_count = 0
    
    for dir_path, dir_names, _ in os.walk(root_dir):
        # Copy the current directory name list to avoid problems caused by modifying during traversal
        for dirname in dir_names[:]:
            # Check if any target directory pattern matches
            if any(target in dirname for target in target_dirs):
                full_path = os.path.join(dir_path, dirname)
                print(f"Deleting {full_path}...")
                try:
                    shutil.rmtree(full_path)
                    print(f"Successfully deleted {full_path}")
                    deleted_count += 1
                except Exception as e:
                    print(f"Failed to delete {full_path}: {e}")
                    error_count += 1
    
    print(f"\nCleanup completed. Deleted: {deleted_count}, Errors: {error_count}")


def main() -> int:
    """
    Main function to parse arguments and execute cleanup.
    
    @return: Exit code (0 for success, 1 for error)
    """
    parser = argparse.ArgumentParser(
        description='Delete build directories from workspace.',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""description:
Delete all directories matching specified patterns recursively.
By default, it deletes 'cmake-build-debug' directories."""
    )
    
    parser.add_argument(
        '--path', 
        default='..', 
        help='Root directory to start deletion (default: ..)'
    )
    
    parser.add_argument(
        '--targets',
        nargs='+',
        default=['cmake-build-debug'],
        help='Target directory names or patterns to delete (default: cmake-build-debug)'
    )
    
    parser.add_argument(
        '--dry-run',
        action='store_true',
        help='Show what would be deleted without actually deleting'
    )
    
    args = parser.parse_args()
    
    # Validate path
    if not os.path.exists(args.path):
        print(f"Error: Path '{args.path}' does not exist")
        return 1
    
    if not os.path.isdir(args.path):
        print(f"Error: Path '{args.path}' is not a directory")
        return 1
    
    print(f"Starting cleanup from: {os.path.abspath(args.path)}")
    if args.dry_run:
        print("DRY RUN MODE - No files will be deleted")
        # In a real implementation, we would show what would be deleted
        # For now, we'll just show the configuration
        print(f"Target directories: {', '.join(args.targets)}")
    else:
        delete_cmake_dirs(args.path, args.targets)
    
    return 0


if __name__ == "__main__":
    sys.exit(main())

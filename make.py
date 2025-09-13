import os
import subprocess
import glob
import shutil
import sys
import argparse
import platform

def main():

    # Define default prefix
    if (platform.system() == "Windows"):
        install_prefix = "C:\\Program Files\\gore"
    else:
        install_prefix = "out/release"

    # Setup argument parser
    parser = argparse.ArgumentParser(description='Build script with Conan and CMake')
    parser.add_argument('--prefix', type=str, default=install_prefix,
                        help='Set CMAKE_PREFIX_PATH for CMake')
    parser.add_argument('--clean', action='store_true',
                        help='Delete old build files without prompting')
    parser.add_argument('--no-clean', action='store_true',
                        help='Skip cleaning old build files')
    parser.add_argument('--build-type', type=str, default='Release',

                        choices=['Release', 'Debug', 'RelWithDebInfo', 'MinSizeRel'],
                        help='Build configuration type')
    
    args = parser.parse_args()

    # Install prefix
    install_prefix = os.path.normpath(args.prefix)

    # Check required programs
    required_programs = ["cmake", "conan"]


    def check_program_exists(program_name):
        path = shutil.which(program_name)
        if path is None:
            print(f"ERROR: Program '{program_name}' not found in PATH.")

            return False
        else:
            print(f"Found '{program_name}' at: {path}")
            return True


    all_found = True
    for prog in required_programs:

        if not check_program_exists(prog):
            all_found = False

    if not all_found:
        print("ERROR: Not all required programs are available. Aborting.")
        sys.exit(1)
    else:
        print("All required programs found. Proceeding.")

    # Handle cleaning
    if args.clean:
        print("Deleting old files (--clean flag specified)")
        shutil.rmtree(install_prefix, ignore_errors=True)
        shutil.rmtree("out", ignore_errors=True)
    elif not args.no_clean:
        delete = input("Delete old files? (Y/n): ")
        if delete.lower() == "y" or delete == "":
            shutil.rmtree("out", ignore_errors=True)
        elif delete.lower() == "n":
            pass
        else:
            print("Wrong user prompt")
            sys.exit(0)

    os.makedirs('out', exist_ok=True)
    os.makedirs('out/release', exist_ok=True)
    print('Out directory created or already exists')

    # Start conan
    conan_cmd = ["conan", "install", ".", "-of", "out", "--build", "missing"]
    subprocess.run(conan_cmd, check=True)

    try:

        os.remove("./CMakeUserPresets.json")
    except OSError:
        print("CMakeUserPreset does not exist")

    conan_toolchain_path = ""
    for f in glob.glob(f'{os.getcwd()}/out/**/conan_toolchain.cmake', recursive=True):
        conan_toolchain_path = os.path.normpath(f)
 
    # Configure CMake
    cmake_cmd = [
        "cmake", "-S", ".", "-B", "out",
        f"-DGORE_CONAN_TOOLCHAIN_PATH={conan_toolchain_path}",
        f"-DCMAKE_INSTALL_PREFIX={install_prefix}",
        f"-DCMAKE_BUILD_TYPE={args.build_type}"
    ]

    # Add prefix argument if provided
    if args.prefix:
        cmake_cmd.append(f"-DCMAKE_PREFIX_PATH={args.prefix}")


    subprocess.run(cmake_cmd, check=True)

    # Build
    subprocess.run(["cmake", "--build", "out", "--config", args.build_type], check=True)


    # Install
    subprocess.run(["cmake", "--install", "out", "--config", args.build_type], check=True)

    if (platform.system() == "Linux"):
        try:
            if (os.path.isfile("compile_commands.json")):
                os.remove("compile_commands.json")
            # Move compile_commands to root
            shutil.move("out/compile_commands.json", ".")
        except:
            print(sys.exc_info())
            print("Cannot move compile_commands.json to root folder")

    

if __name__ == "__main__":
    main()

### Author: satanisticmicrowave

import os
import subprocess
import glob
import shutil
import sys

# Check programs
required_programs = [
    "cmake",
    "conan" 
]

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


shutil.rmtree("out", ignore_errors=True)
os.makedirs('out', exist_ok=True)
os.makedirs('out/release')
print('Out directory created or already exist')

# Start conan
subprocess.run(["conan", "install", ".", "-of", "out", "--build", "missing"])

try:
    os.remove("./CMakeUserPresets.json")
except OSError as error:
    print("CMakeUserPreset does not exists")

conan_toolchain_path = ""
for f in glob.glob(f'{os.getcwd()}/out/**/conan_toolchain.cmake', recursive=True):
    conan_toolchain_path = os.path.normpath(f)

# configure
subprocess.run([
    "cmake", "-S", ".", "-B", "out",
    f"-DGORE_CONAN_TOOLCHAIN_PATH={conan_toolchain_path}",
    "-DCMAKE_INSTALL_PREFIX=out/release"
], check=True)

# build
subprocess.run(["cmake", "--build", "out"], check=True)

# install
subprocess.run(["cmake", "--build", "out", "--target", "install"], check=True)



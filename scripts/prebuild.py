"""
PlatformIO pre-build script
"""

import os
import datetime

def main(env):
    """Main function called by PlatformIO"""
    print("Pre-build script is running...")
    
    # Get environment info
    build_date = datetime.datetime.now().strftime("%Y-%m-%d")
    build_time = datetime.datetime.now().strftime("%H:%M:%S")

    # Add build date and time flags
    env.Append(CPPDEFINES=[
        ("BUILD_DATE", "\\\"" + build_date + "\\\""),
        ("BUILD_TIME", "\\\"" + build_time + "\\\"")
    ])

    print(f"Build date: {build_date}")
    print(f"Build time: {build_time}")

    # Create version.h file
    version_file_path = os.path.join(env.get('PROJECT_DIR'), 'include', 'version.h')
    print(f"Generating version file: {version_file_path}")

    # Make sure the include directory exists
    include_dir = os.path.dirname(version_file_path)
    if not os.path.exists(include_dir):
        os.makedirs(include_dir)

    # Get version info from environment or use defaults
    version_major = "1"
    version_minor = "0"
    version_patch = "0"

    # Write to file
    with open(version_file_path, 'w') as f:
        f.write("#ifndef VERSION_H\n")
        f.write("#define VERSION_H\n\n")
        f.write(f"#define VERSION_MAJOR {version_major}\n")
        f.write(f"#define VERSION_MINOR {version_minor}\n")
        f.write(f"#define VERSION_PATCH {version_patch}\n")
        f.write(f"#define VERSION_STRING \"{version_major}.{version_minor}.{version_patch}\"\n")
        f.write(f"#define BUILD_DATE \"{build_date}\"\n")
        f.write(f"#define BUILD_TIME \"{build_time}\"\n\n")
        f.write("#endif // VERSION_H\n")

    print("Pre-build script completed successfully")

# When PlatformIO runs this script, it provides the env
Import("env")
main(env) 
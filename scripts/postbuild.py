"""
PlatformIO post-build script
"""

import os
import sys
import datetime
import shutil

def main(env):
    """Main function called by PlatformIO"""
    print("Post-build script is running...")

    # Get environment info
    project_dir = env.get('PROJECT_DIR', '')
    build_dir = env.get('BUILD_DIR', '')
    firmware_path = env.get('FIRMWARE_PATH', '')

    # Check if build was successful
    if not firmware_path or not os.path.exists(firmware_path):
        print(f"Warning: Firmware not found at {firmware_path}")
        print("This is normal if no source files were compiled.")
        print("Post-build script completed with warnings")
        return

    # Create output directory
    output_dir = os.path.join(project_dir, 'build_output')
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # Generate output filename with timestamp
    timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
    firmware_name = os.path.basename(firmware_path)
    output_firmware = os.path.join(output_dir, f"{os.path.splitext(firmware_name)[0]}_{timestamp}{os.path.splitext(firmware_name)[1]}")

    # Copy firmware to output directory
    print(f"Copying firmware to: {output_firmware}")
    shutil.copy2(firmware_path, output_firmware)

    print("Post-build script completed successfully")

# When PlatformIO runs this script, it provides the env
Import("env")
main(env) 
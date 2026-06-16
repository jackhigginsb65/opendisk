![opendisk logo](assets/opendisk_logo.png)

#opendisk

opendisk is a fast, lightweight, disk usage analyzer for Linux made in C++.

## Performance
In raw filesystem races crawling root ('/') directories, opendisk outpaces legacy utilities by elimated bloat and executing a lean, modern memory-mapped sort

Based in identical environments:
* **'sudo du -ah /'**: ~1.62 seconds
* **'sudo opendisk /'**: **~0.49 seconds** (~3x faster!)

## Features
* **True Disk Allocation** Computes allocation footprints based on physical hardware blocks ('st_blocks') rather than text byte sizing.
* **Hard link deduplication:** Tracks underlying system node IDs ('inodes') to elimate duplicate counting on system utilities.
* **Partition Guarding:** Automatic cross-filesystem protection ('FTW_MOUNT') ensuring external storage setups (like dual-boot environments) are never actually polled.

## Installation and cleanup

Ensure that you have a modern GCC compiler that supports C++17. The makefile uses g++.

'''bash
# Clone the repository
git clone [https://github.com/jackhigginsb65/opendisk(https://github.com/jackhigginsb65/opendisk)
cd opendisk

# Build the binary
make

# Install system-wide (optional)
sudo make install
make clean

# Uninstall
sudo make remove
'''

## Project
[https://github.com/jackhigginsb65/opendisk(https://github.com/jackhigginsb65/opendisk)

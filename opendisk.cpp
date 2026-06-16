#include <iostream>
#include <ftw.h>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <set>

#define OPENDISK_MSG "\033[1;36m[opendisk]\033[0m "

struct Entry {
	std::string path;
	size_t size;
};


std::vector<std::string> units = {"B", "KB", "MB", "GB", "TB"};
std::vector<Entry> files;
std::set<ino_t> seen_inodes;

int function(const char *path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
	if (typeflag == FTW_DNR || typeflag == FTW_NS) {
		return 0;
	}

	size_t filesize = sb->st_blocks * 512;

	if (S_ISREG(sb->st_mode)) {
		auto [iterator, inserted] = seen_inodes.insert(sb->st_ino);
		if (!inserted) {
			filesize = 0;
		}
	}
	
	files.push_back({std::string(path), filesize});

	return 0;
}

void unit_precision(int y) {
	if (y == 0) {std::cout << std::setprecision(0); }
	else {std::cout << std::setprecision(2);  }
}

void print_files() {
	int pc = -1;          //Print_count
			      //Leftovers after pc reaches its limit (if statement 3 lines below)
	size_t leftoverb = 0; //leftover bytes
	int leftoverf = 0;    //leftover files
			      //
	double totalb = 0;    // Total bytes
	for (const auto& file : files) {
		pc++;
		totalb += file.size;
		if (pc < 15) {
			double x = file.size;
			int y = 0;

			while (x >= 1024 && y < units.size() -1) {
				x /= 1024.0;
				y++;
			}

			std::cout << std::fixed;

			unit_precision(y);
		
			std::cout << x << units[y] << "\t" << file.path << "\n";
		} else { 
			leftoverb += file.size;
			leftoverf++;
		}
	}
	int y = 0;
	double final_size = leftoverb;

	if (leftoverf > 0) {
		while (final_size >= 1024 && y < units.size() -1) {
			final_size /= 1024.0;
			y++;
		}

		unit_precision(y);

		std::string x = (leftoverf > 1) ? "files" : "file";   //This is completely unrelated to the previous x variable
		
		std::cout << "And " << leftoverf << " more " << x << " totaling to " << final_size << units[y] << "\n";
	}
	y = 0;
	while (totalb >= 1024 && y < units.size() -1) {
		totalb /= 1024.0;
		y++;
	}

	unit_precision(y);

	size_t  totalf = files.size(); // Total files set equal to size of files vector
	std::string x = (totalf > 1) ? "files" : "file";  //Once again completely unrelated to the other x variables

	std::cout << OPENDISK_MSG << "Total storage used: " << totalb << units[y] << " across " << totalf << " " << x << "\n";

}

int main(int argc, char* argv[]) {

	files.clear();
	seen_inodes.clear();

	std::cout << OPENDISK_MSG << "Running..\n";

	std::string target_path = ".";

	if (argc > 1) {
		target_path = argv[1];
	}

	nftw(target_path.c_str(), function, 10, FTW_PHYS | FTW_MOUNT);

	std::sort(files.begin(), files.end(), [](const Entry& a, const Entry& b) {
			return a.size > b.size;
	});

	print_files();

	return 0;
}

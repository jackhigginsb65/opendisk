#include <iostream>
#include <ftw.h>
#include <vector>
#include <string>
#include <iomanip>

#define OPENDISK_MSG "\033[1;36m[opendisk]\033[0m "

struct Entry {
	std::string path;
	size_t size;
};


std::vector<std::string> units = {"B", "KB", "MB", "GB", "TB"};
std::vector<Entry> files;

int function(const char *path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
	size_t filesize = sb->st_size;
	
	files.push_back({std::string(path), filesize});

	return 0;
}

void print_files() {
	for (const auto& file : files) {
		double x = file.size;
		int y = 0;

		while (x >= 1024 && y < units.size() -1) {
			x /= 1024.0;
			y++;
		}

		std::cout << std::fixed;

		if (y == 0) { std::cout << std::setprecision(0); }
		else { std::cout << std::setprecision(2); }
		
		std::cout << x << units[y] << "\t" << file.path << "\n";
	}
}

int main() {
	std::cout << OPENDISK_MSG << "opendisk\n";

	nftw(".", function, 5, 0);

	print_files();

	return 0;
}

//Scoreboard.cpp
#include "LocalScoreBoard.hpp"
#include <fstream>
#include <algorithm>
#include <cstdint>
#include <cstring>
using namespace std;

LocalScoreboard::LocalScoreboard() {}

bool LocalScoreboard::load(char const* data_file) {
	ifstream f;
	f.open(data_file, ios::binary);
	if (!f.is_open()) { return false; }

	Entry entry_buffer;
	f.read(reinterpret_cast<char*>(&entry_buffer), SizeOfEntry);
	entries.clear();

	while (!f.eof()) {
		entries.push_back(entry_buffer);
		f.read(reinterpret_cast<char*>(&entry_buffer), SizeOfEntry);
	}
	f.close();
	return true;
}

bool LocalScoreboard::save(char const* data_file) const {
	ofstream f;
	f.open(data_file, ios_base::out | ios_base::binary);
	if (!f.is_open()) { return false; }

	f.write(reinterpret_cast<char const*>(&entries[0]), SizeOfEntry * entries.size());
	f.close();
	return true;
}

int LocalScoreboard::addEntry(Entry const& entry) {
	auto loc = entryWorseThan(entry);
	entries.insert(loc.first, entry);
	return loc.second;
}

LocalScoreboard::Entry LocalScoreboard::getEntry(int index) const {
	return entries[index];
}

void LocalScoreboard::prune(int max_amt) {
	entries.resize(max_amt);
}

int LocalScoreboard::size() const { return entries.size(); }

LocalScoreboard::EntryLocation LocalScoreboard::entryWorseThan(Entry const& entry) {
	int i = 0;
	for (auto it = entries.begin(); it != entries.end(); ++it, ++i) {
		if (it->score <= entry.score) {
			return EntryLocation(it, i);
		}
	}
	return EntryLocation(entries.end(), i);
}

void LocalScoreboard::Entry::setName(std::string str) {
	std::memcpy(&name[0], &str.c_str()[0], sizeof(char) * (str.length() + 1));
}
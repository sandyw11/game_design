#ifndef LOCAL_SCORE_BOARD_HPP
#define  LOCAL_SCORE_BOARD_HPP
#include <string>
#include <utility>
#include <vector>

class LocalScoreboard {
public:
	struct Entry {
		char name[256];
		int  score;

		void setName(std::string str);
	};
	typedef std::vector<Entry> Entries;
	typedef std::pair<Entries::iterator, int> EntryLocation;
	LocalScoreboard();

	bool load(char const* data_file);
	bool save(char const* data_file) const;

	int  addEntry(Entry const& entry);
	Entry getEntry(int index) const;

	void prune(int max_amt);
	int  size() const;
private:
	//Not copy-constructable
	LocalScoreboard(LocalScoreboard const&);

	Entries entries;
	static int const SizeOfEntry = sizeof(Entry);

	EntryLocation entryWorseThan(Entry const& entry);
};
#endif
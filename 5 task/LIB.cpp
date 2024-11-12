#include "LIB.h"

namespace EXCEPT {
	const char* Except::what() const noexcept {
		return message.c_str();
	}

	Except::Except(const std::string text): message(text) { }

	Except::~Except() {	}
    
}

namespace CMP {
	int cmp (const std::string str1, const std::string str2) {
        if (cmplen(str1, str2) != 0) return cmplen(str1, str2);
        if (str1 > str2) return 1;
        if (str1 < str2) return -1;

        return 0;
    }
    
    int cmplen (const std::string str1, const std::string str2) {
        if (str1.length() < str2.length()) return -1;
        if (str1.length() > str2.length()) return 1;
        return 0;
    }
    
}

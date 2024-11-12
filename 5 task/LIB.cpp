#include "LIB.h"

namespace EXCEPT {
	const char* Except::what() const noexcept {
		return message.c_str();
	}

	Except::Except(const std::string text): message(text) { }

	Except::~Except() {	}
    
}

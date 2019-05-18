// Copyright [2019] <Alek Frohlich, Gabriel B. Sant'Anna>
#include "xml.h"

#include <string>
#include <cstddef>

#include "linked_stack.h"


namespace xml {

bool balanced(const std::string& xml) {
	structures::LinkedStack<std::string> tags;

	auto from = 0u;
	while (from < xml.length()) {
		// check for tag
		const auto tag_open = xml.find('<', from);
		const auto tag_close = xml.find('>', tag_open);

		// no tag found
		if (tag_open == std::string::npos)
			break;

		// incomplete tag
		if (tag_close == std::string::npos)
			return false;

		// get tag
		auto tag = xml.substr(tag_open, tag_close + 1 - tag_open);
		from = tag_close + 1;

		// if its an opening tag, push the closing one
		if (tag[1] != '/') {
			tags.push(tag.insert(1, "/"));
		}
		// otherwise (if its a closing tag), check if it was expected
		else {
			if (tags.empty())
				return false;
			else if (tags.top() == tag)
				tags.pop();
			else
				return false;
		}
	}

	// all tags must have been closed
	return tags.empty();
}


std::string extract(const std::string& origin,
                    const std::string& open, const std::string& close,
                    std::size_t& from)
{
	auto open_pos = origin.find(open, from);
	const auto close_pos = origin.find(close, open_pos);

	if (open_pos == std::string::npos || close_pos == std::string::npos) {
		from = std::string::npos;
		return "";
	}

	from = close_pos + close.length();
	open_pos += open.length();
	return origin.substr(open_pos, close_pos - open_pos);
}

std::string extract(const std::string& origin,
                    const std::string& open, const std::string& close)
{
	std::size_t pos{0};
	return extract(origin, open, close, pos);
}

}  // namespace xml

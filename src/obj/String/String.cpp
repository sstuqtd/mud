//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Config.h>
#include <obj/String/String.h>
#include <obj/String/StringConvert.h>
#include <obj/Strung.h>

#include <algorithm>

namespace mud
{
	bool strung::operator==(const strung& other) const
	{
		return strcmp(m_buffer, other.m_buffer) == 0;
	}

	bool strung::operator==(cstring other) const
	{
		return strcmp(m_buffer, other) == 0;
	}

	template MUD_OBJ_EXPORT void from_string(const string& str, float& val);
	template MUD_OBJ_EXPORT void to_string(const float& val, string& str);

	const size_t g_num_precision = 3;

	void split_string(const string& str, const string& separator, array<string> output)
	{
		size_t start = 0;
		size_t next = str.find(separator, start);

		size_t index = 0;
		while(next != string::npos && index < output.size())
		{
			output[index++].assign(str.data() + start, next - start);
			start = next + 1;
			next = str.find(separator, start);
		}
		if(index < output.size())
			output[index++].assign(str.data() + start, str.size() - start);
	}

	std::vector<string> split_string(const string& str, const string& separator)
	{
		std::vector<string> result;
		
		if(str.size() == 0)
			return result;

		size_t cur_pos = 0;
		size_t last_pos = 0;

		while (cur_pos != string::npos)
		{
			cur_pos = str.find(separator, last_pos);
			result.push_back(str.substr(last_pos, cur_pos - last_pos));
			last_pos = cur_pos + separator.size();
		}

		return result;
	}

	string replace_all(const string& original, const string& before, const string& after)
	{
		string retval;
		string::const_iterator end = original.end();
		string::const_iterator current = original.begin();
		string::const_iterator next = std::search(current, end, before.begin(), before.end());
		while(next != end)
		{
			retval.append(current, next);
			retval.append(after);
			current = next + before.size();
			next = std::search(current, end, before.begin(), before.end());
		}
		retval.append(current, next);
		return retval;
	}

	string to_lower(const string& original)
	{
		string result = original;
		std::transform(result.begin(), result.end(), result.begin(), ::tolower);
		return result;
	}

	string to_upper(const string& original)
	{
		string result = original;
		std::transform(result.begin(), result.end(), result.begin(), ::toupper);
		return result;
	}

	string to_camelcase(const string& name)
	{
		string result = name;
		for(size_t pos = result.find('_'); pos != string::npos; pos = result.find('_', pos))
		{
			result.erase(pos, 1);
			result[pos] = char(::toupper(result[pos]));
		}
		return result;
	}
}

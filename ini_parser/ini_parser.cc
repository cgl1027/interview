#include "ini_parser.h"
#include <fstream>

namespace qh
{
	bool INIParser::Parse(const std::string& ini_file_path)
	{
		std::ifstream input_file(ini_file_path.c_str());

		if(!input_file) 
			return false;

		std::string input_line;

		while (getline(input_file, input_line)) {
			Parse(input_line.c_str(), input_line.size());
		}

		input_file.close();

		return true;
	}

	bool INIParser::Parse(const char* ini_data, size_t ini_data_len,\
						  const std::string& line_seperator, \
						  const std::string& key_value_seperator)
	{
		if(ini_data == NULL || ini_data_len < 0)
			return false;

		ini_data_ = std::string(ini_data);

		size_t pos_cur = 0;
		size_t pos_next = 0;
		std::string key_val;

		while (pos_next < ini_data_len)
		{
			pos_next = findNextSeper(ini_data_, pos_cur, line_seperator);  //首先找到最近的一个行数据分隔符
			key_val = ini_data_.substr(pos_cur, pos_next - pos_cur);       //将得到的字符串根
			splitKeyVal(key_val, keyVal_map_, key_value_seperator);	       //据分隔符分成key和value
			pos_next += line_seperator.size();			       //继续向下搜索下一个行数据分隔符
			pos_cur = pos_next;
		}
		
		return true;
	}

	size_t INIParser::findNextSeper(const std::string& ini_data, size_t pos, const std::string& seperator)
	{
		while(pos < ini_data.size())
		{
			if (ini_data[pos] == seperator[0])
			{
				if(ini_data.substr(pos, seperator.size()) == seperator)
					break;
			}
			++pos;
		}
		return pos;
	}

	void INIParser::splitKeyVal(const std::string& key_val,\
				    std::map<std::string,std::string>& keyVal_map,\
				    const std::string& key_val_seperator)
	{
		if(key_val.size() == 0) return;
		size_t pos = 0;
		while(pos < key_val.size())
		{
			if (key_val[pos] == key_val_seperator[0])
			{
				if (key_val.substr(pos, key_val_seperator.size()) == key_val_seperator)
					break;
			}
			++pos;	
		}

		size_t temp = pos + key_val_seperator.size();
		std::string key = key_val.substr(0, pos);
		std::string val = key_val.substr(temp, key_val.size() - temp);
		keyVal_map.insert(make_pair(key, val));
	}

	const std::string& INIParser::Get(const std::string& key, bool* found)
	{
		std::map<std::string, std::string>::iterator it;
		if ((it = keyVal_map_.find(key)) != keyVal_map_.end())
		{
			if(found)
				*found = true;
			return it->second;
		}
		if(found)
			*found = true;
		return empty_str_;
	}

	const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found)
	{
		if(Parse(section.c_str(), section.size()))
			return Get(key, found);
		return empty_str_;
	}
}

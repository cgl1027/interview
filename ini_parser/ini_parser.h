#ifndef QIHOO_INI_PARSER_H_
#define QIHOO_INI_PARSER_H_

#include <string>
#include <map>

namespace qh
{
    class INIParser
    {
    public:
        INIParser(){}
        ~INIParser(){}

        //! \brief 解析一个磁盘上的INI文件
        //! \param[in] - const std::string & ini_file_path
        //! \return - bool
        bool Parse(const std::string& ini_file_path);

        //! \brief 解析一段形如INI格式的内存数据。
        //!   例如：ini_data="a:1||b:2||c:3"
        //!         调用<code>Parse(ini_data, ini_data_len, "||", ":")</code>即可解析出这段数据。
        //!         解析完毕之后 
        //!         Get("a")=="1" && Get("b")=="2" && Get("c")=="3"
        //! \param[in] - const char * ini_data
        //! \param[in] - size_t ini_data
        //! \param[in] - const std::string & line_seperator
        //! \param[in] - const std::string & key_value_seperator
        //! \return - bool
        bool Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator = "\n", const std::string& key_value_seperator = "=");

        //! \brief 从默认section中查找某个key，并返回找到的value。如果找不到，返回一个空串
        //! \param[in] - const std::string & key
        //! \param[in] - bool * found - 输出参数，true表明找到这个key
        //! \return - const std::string& - 返回的具体key对应的value
        const std::string& Get(const std::string& key, bool* found);

        const std::string& Get(const std::string& section, const std::string& key, bool* found);

    private:
		/*
			findNextSeper用于找到下一个分割点，返回下一个分割点字符串起始位置坐标
			ini_data:输入的数据
			pos: 在输入的数据中开始查找的位置
			seperator: 分割数据的字符串
		*/
		size_t findNextSeper(const std::string& ini_data, size_t pos, const std::string& seperator);

		/*
			在只有key和value的字符串中分割key和value
			key_val: 经过切割后只含有key和value的字符串
			mulmap: map容器，用于存放分割后得到的key和对应的value
			key_val_seperator: 分割key和val的字符串
		*/
		void splitKeyVal(const std::string& key_val,\
						 std::map<std::string,std::string>& mulmap,\
						 const std::string& key_val_seperator);

		std::map<std::string, std::string> keyVal_map_;               //保存key和value的值
		std::string ini_data_;										  //保存初始的字符串数据
		const std::string empty_str_;								  //Get函数获取不到key时的空字符串引用
    };
}

#endif


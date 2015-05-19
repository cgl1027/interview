#include "qh_string.h"
#include <stdio.h>
#include <string.h>

namespace qh
{
    // TODO 将在这里写实现代码

    string::string()
        : len_(0)
    {
		data_ = new char[1];
		data_[0] = '\0';
    }

    string::string( const char* s )
    {
		if(s == NULL)
		{
			data_ = new char[1];
			data_[0] = '\0';
			len_ = 0;
		}
		else
		{
			len_ = strlen(s);
			data_ = new char[len_ + 1];
			strcpy(data_, s);	
		}	
    }

    string::string( const char* s, size_t len )
    {
		if(s == NULL || len < 1)
		{
			data_ = new char[1];
			data_[0] = '\0';
			len_ = 0;
		}
		else if(len >= strlen(s))
		{
			len_ = strlen(s);
			data_ = new char[len_ + 1];
			strcpy(data_, s);	
		}
		else
		{
			data_ = new char[len + 1];
			len_ = len;
			int i = 0;
			char* curpos = data_;
			while (i++ < len)
				*curpos++ = *s++;
			*curpos = '\0';
		}	
    }

    string::string( const string& rhs )
    {
		len_ = rhs.len_;
		data_ = new char[len_ + 1];
		strcpy(data_, rhs.data());
    }

    string& string::operator=( const string& rhs )
    {
        if(this == &rhs) return *this;

		char* tmp_data = data_;

		data_ = new char[rhs.len_ + 1];
		strcpy(data_, rhs.data_);
		len_ = rhs.len_;

		delete[] tmp_data;
		return *this;
    }

    string::~string()
    {
		delete[] data_;
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        return data_;
    }

    const char* string::c_str() const
    {
        return data_;
    }

    
	char& string::operator[]( size_t index )
	{
		if(index >= len_)
		{
			fprintf(stderr, "index of string out of rage.\n");
			exit(1);
		}
		return data_[index];
	}

	const char& string::operator[]( size_t index ) const
    {
        if(index >= len_)
		{
			fprintf(stderr, "index of string out of rage.\n");
			exit(1);
		}
		return data_[index];
    }
}

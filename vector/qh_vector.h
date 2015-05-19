#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_

namespace qh
{
    template<class T>
    class vector {
    public:
        //ctor
        vector()
            : data_(NULL), size_(0), capacity_(0)
        {
        }

        vector( size_t n, const T& value = T())
        {
            capacity_ = DoubleSize(n);
			data_ = new T[capacity_];
            for (size_t i = 0; i < n; i++)
            {
                data_[i] = value;
            }
			size_ = n;
        }

		vector(vector<T>& rhs)
		{
			capacity_ = rhs.capacity_;
			data_ = new T[capacity_];
			for (size_t i = 0; i < rhs.size_; i++)
			{
				data_[i] = rhs[i];
			}
			size_ = rhs.size_;
		}

		vector& operator=(const vector& rhs);

        //dtor
        ~vector()
        {
			delete[] data_;
        }

        //get
        size_t size() const
        {
            return size_;
        }

        // set & get
        T& operator[](size_t index) const;

        // set
        void push_back(const T& element);
        void pop_back();
        void resize(size_t n, const T& element = T());
        void reserve(size_t n);
        void clear();
        void empty() {return size_ == 0;}

    private:
        T*      data_;
        size_t  size_;                          //data_的有效数据大小
	size_t  capacity_;			//data_的实际容量大小

	size_t DoubleSize(size_t s)     	//用于计算capacity_, capacity_总是大于等于有效数据个数的
	{					//2的整数幂，从而防止push_back()时频繁复制数据
		size_t res = 0x1;
		while(res < s) res <<= 1;
		return res;
	}
    };

	template<class T>
	vector<T>& vector<T>::operator=(const vector<T>& rhs)
	{
		if(this == &rhs) return *this;
		delete[] data_;
		data_ = new T[rhs.capacity_];
		size_ = rhs.size_;
		capacity_ = rhs.capacity_;
		for (size_t i = 0; i < rhs.size_; i++)
		{
			(*this)[i] = rhs[i];
		}
		return *this;
	}

	template<class T>
	T& vector<T>::operator[](size_t index) const
	{
		if(index >= size_)
		{
			fprintf(stderr, "index is out of range.\n");
			exit(1);
		}
		return data_[index];
	}

	template<class T>
	void vector<T>::push_back(const T& element)
	{
		if (size_ == capacity_)							
		{												
			T* tep_data = data_;

			capacity_ = DoubleSize(size_+1);	
			data_ = new T[capacity_];

			for (size_t i = 0; i < size_; ++i)
				data_[i] = tep_data[i];

			data_[size_] = element;
			++size_;
			delete[] tep_data;
		}
		else											
		{
			data_[size_] = element;
			++size_;
		}
	}


	template<class T>
	void vector<T>::pop_back()
	{
		if(size_ > 0)  --size_;			
		if(size_ == 0) clear();		        //如果删除后data_为空，则运行clear()
	}

	template<class T>
	void vector<T>::resize(size_t n, const T& element)
	{
		if(n > size_)
		{
			for (size_t i = size_; i < n; ++i)
			{
				push_back(element);
			}
		}
		size_ = n;
	}

	template<class T>
	void vector<T>::reserve(size_t n)
	{
		if(n > capacity_)
		{
			T* tep_data = data_;
			data_ = new T[n];
			capacity_ = n;
			for(int i = 0; i < size_; ++i)
				data_[i] = tep_data[i];
			delete[] tep_data;
		}
	}

	template<class T>
	void vector<T>::clear()
	{
		delete[] data_;
		data_ = NULL;
		size_ = 0;
		capacity_ = 0;
	}
}

#endif



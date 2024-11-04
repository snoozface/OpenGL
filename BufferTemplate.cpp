	
	template <typename T>
	void Buffer::uploadBuffer(const std::vector<T>& data, GLenum usage)
	{
		bindBuffer();
		if constexpr (std::is_same_v<T, int>)
		{
			uploadIntData(data, usage);
		}
		else if constexpr (std::is_same_v<T, float>)
		{
			uploadFloatData(data, usage);
		}
		else
		{
			std::cerr << "ERROR: Buffer::uploadBuffer called with invalid data type\n";
		}
	}
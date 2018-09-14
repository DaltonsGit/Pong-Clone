#pragma once

#include <vector>

class IndexBuffer {

private:
	unsigned int m_RendererID;
	unsigned int m_Count;

public:
	IndexBuffer();
	//Size always in bytes, count means element count.
	IndexBuffer(std::vector<unsigned int> &data , unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
}; 
#pragma once
#include <vector>

class VertexBuffer {

private:
	unsigned int m_RendererID;

public:
	VertexBuffer();
	VertexBuffer(/*const void* data*/ std::vector<float> &data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

};
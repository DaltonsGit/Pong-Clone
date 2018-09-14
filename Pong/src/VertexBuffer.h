#pragma once
#include <vector>

class VertexBuffer {

private:
	unsigned int m_RendererID;

public:
	VertexBuffer();
	VertexBuffer(std::vector<float> &data, unsigned int size);

	void subData(std::vector<float> data);

	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

};
/** \file bufferLayout.h
*/
#pragma once

#include <vector>

#include "OpenGL/ShaderDataTypes.h"

namespace IMAT3905 {


	/**
	\class VertexBufferElement
	A class which hold data about a single element in a vertexBuffer
	*/
	class VertexBufferElement {
	public:
		ShaderDataType m_dataType;
		size_t m_size;
		size_t m_offset;
		bool m_normalised;

		VertexBufferElement() {}; //!< Default constructor
		VertexBufferElement(ShaderDataType dataType, bool normalised = false) :
			m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalised(normalised) {};
	};

	/**
	\class UniformBufferElement
	A class which hold data about a single element in a uniformBuffer
	*/
	class UniformBufferElement {
	public:
		ShaderDataType m_dataType;
		size_t m_size;
		size_t m_offset;

		UniformBufferElement() {}; //!< Default constructor
		UniformBufferElement(ShaderDataType dataType) :
			m_dataType(dataType), m_size(align(ShaderDataTypeSize(dataType),16)), m_offset(0) {};
	private:
		int align(int number, int alignment)
		{
			int remainder = number % alignment;
			if (remainder == 0) return number;

			return number + alignment - remainder;
		}
	};

	/**
	\class BufferLayout
	A class which hold the layout of a vertex or uniform buffer as a collection of VertexBufferElements or UniformBufferElements.
	Can be exracted from shader source code or initilisaed manually.
	*/

	template<class G>
	class BufferLayout
	{
	private:
		std::vector<G> m_elements; // Buffer elements
		size_t m_stride; // Stride - distance between data lines
		void calcStrideAndOffsets(); // Calculate the stride distance and the offset for each element
	public:
		BufferLayout() {}; //!< Default constructor
		BufferLayout(const std::initializer_list<G>& elements); // Constructor through which layout elements are passed
		inline void setStride(size_t stride) { m_stride = stride; }
		inline size_t getStride() const { return m_stride; }
		typename std::vector<G>::iterator begin() { return m_elements.begin(); }
		typename std::vector<G>::iterator end() { return m_elements.end(); }
		typename std::vector<G>::const_iterator begin() const { return m_elements.begin(); }
		typename std::vector<G>::const_iterator end() const { return m_elements.end(); }
		void addElement(ShaderDataType datatype);
	};

	template<class G>
	BufferLayout<G>::BufferLayout(const std::initializer_list<G>& elements) : m_elements(elements)
	{
		calcStrideAndOffsets();
	}

	template<class G>
	void BufferLayout<G>::calcStrideAndOffsets()
	{
		size_t l_offset = 0; // Offset is distance from start of dataline

		for (auto& element : m_elements)
		{
			element.m_offset = l_offset;
			l_offset += element.m_size;
		}

		m_stride = l_offset; // Stride is distance between dataline - so the sum of all element sizes
	}

	template<class G>
	void BufferLayout<G>::addElement(ShaderDataType datatype)
	{
		m_elements.push_back(G(datatype));
		calcStrideAndOffsets();
	}

	using VertexBufferLayout = BufferLayout<VertexBufferElement>;
	using UniformBufferLayout = BufferLayout<UniformBufferElement>;


	

	

	
}

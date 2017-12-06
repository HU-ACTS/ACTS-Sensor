/**
* @file doubleBuffer.hpp
* @Author Jop van Buuren.
* @data 21 september, 2017
* @brief switching buffer
*/
#pragma once

#include "BaseTask.hpp"
#include "BinaryBuffer.hpp"
#include "SDWriter.hpp"

class DoubleBuffer{
public:
	DoubleBuffer(SDWriter&);
	void storeData(SampleData in );
	void swap();
	void emptyBuffer();
	void writeToSd();
	~DoubleBuffer();
private:
	SDWriter &writer;
	BinaryBuffer * firstBuffer;
	BinaryBuffer * secondBuffer;
	BinaryBuffer * current;
	BinaryBuffer * next;
};

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MSF.h"



namespace MSF {


	std::string signExampleString("SIGN EXAMPLE");
	const byteArray signExample(signExampleString.begin(), signExampleString.end());

#pragma region fileRead

	fileRead::fileRead() : m_isDataSign(false), m_sizeFich(0) {
	}

	fileRead::fileRead(std::string path, byteArray signFile) : m_signFile(signFile) {
		std::ifstream::open(path, std::ios::binary | std::ios::in);
		if (isvalid()) {
			m_name = path;
			m_sizeFich = getsizeifstream(*this);
			if (m_sizeFich > m_signFile.size()) {
				byteArray buf(m_signFile);
				std::ifstream::read(reinterpret_cast<char *>(buf.data()), m_signFile.size());
				if (m_isDataSign = buf == m_signFile; !m_isDataSign)
					std::ifstream::seekg(std::ios::beg);
			}
		}
	}

	bool fileRead::open(std::string path) {
		std::ifstream::open(path, std::ios::binary | std::ios::in);
		if (isvalid()) {
			m_name = path;
			m_sizeFich = getsizeifstream(*this);
			if (m_sizeFich > m_signFile.size()) {
				byteArray buf;
				std::ifstream::read(reinterpret_cast<char *>(buf.data()), m_signFile.size());
				if (m_isDataSign = buf == m_signFile; !m_isDataSign)
					std::ifstream::seekg(std::ios::beg);
			}
		}
		return isvalid();
	}

	byteArray fileRead::getbloc(size_t sizeBloc) {
		byteArray buf;
		if (isvalid()) {
			if (size_t dataRemaining = getdatasizeremaining(*this); dataRemaining < sizeBloc) {
				buf.resize(dataRemaining);
				std::ifstream::read(reinterpret_cast<char *>(buf.data()), dataRemaining * sizeof(char));
				std::ifstream::close();
				m_isDataSign = false;
				m_name = "";
				m_sizeFich = 0;
			}
			else {
				buf.resize(sizeBloc);
				std::ifstream::read(reinterpret_cast<char *>(buf.data()), sizeBloc);
			}
		}
		return buf;
	}

	size_t fileRead::gettotalsize() const { return m_isDataSign ? m_sizeFich - m_signFile.size() : m_sizeFich; }

#pragma endregion


#pragma region fileWrite

	size_t fileWrite::getsizedatawritten() { return m_isDataSign ? getsizeifstream(*this) - m_signFile.size() : getsizeifstream(*this); }

	fileWrite::fileWrite() : m_isDataSign(false) {
	}

	fileWrite::fileWrite(std::string path, byteArray signFile, bool isDataCypt) : m_isDataSign(isDataCypt), m_name(path), m_signFile(signFile) {
		std::ofstream::open(m_name, std::ios::binary | std::ios::out);
		if (isvalid()) {
			if (m_isDataSign) {
				std::ofstream::write(reinterpret_cast<char *>(m_signFile.data()), m_signFile.size());
			}
			return;
		}
		m_name = "";
		m_isDataSign = false;
	}

	bool fileWrite::open(std::string path, bool isDataCrypt) {
		m_isDataSign = isDataCrypt;
		m_name = path;
		std::ofstream::open(m_name, std::ios::binary | std::ios::out);
		if (isvalid()) {
			if (m_isDataSign) {
				std::ofstream::write(reinterpret_cast<char *>(m_signFile.data()), m_signFile.size());
			}
			return true;
		}
		m_isDataSign = false;
		m_name = "";
		return false;
	}

	void fileWrite::write(byteArray data) {
		if (isvalid())
			std::ofstream::write(reinterpret_cast<char *>(data.data()), data.size());
	}

#pragma endregion

}
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>
#include "MSF.h"


namespace MSF {

	const std::string signExampleString("SIGN EXAMPLE");
	const byteArray signExample(signExampleString.begin(), signExampleString.end());


	fileRead::fileRead() : m_isDataSign(false), m_sizeFich(0) {
	}

	fileRead::fileRead(const std::string& path, byteArray signFile) : m_signFile(signFile) {
		m_instance.open(path, std::ios::binary | std::ios::in);
		if (isvalid()) {
			m_name = path;
			m_sizeFich = getsizeifstream(m_instance);
			if (m_sizeFich > m_signFile.size()) {
				byteArray buf(m_signFile);
				m_instance.read(reinterpret_cast<char *>(buf.data()), m_signFile.size());
				if (m_isDataSign = buf == m_signFile; !m_isDataSign)
					m_instance.seekg(std::ios::beg);
			}
		}
	}

	bool fileRead::open(const std::string& path) {
		m_instance.open(path, std::ios::binary | std::ios::in);
		if (isvalid()) {
			m_name = path;
			m_sizeFich = getsizeifstream(m_instance);
			if (m_sizeFich > m_signFile.size()) {
				byteArray buf;
				m_instance.read(reinterpret_cast<char *>(buf.data()), m_signFile.size());
				if (m_isDataSign = buf == m_signFile; !m_isDataSign)
					m_instance.seekg(std::ios::beg);
			}
		}
		return isvalid();
	}

	byteArray fileRead::getbloc(size_t sizeBloc) {
		byteArray buf;
		if (isvalid()) {
			if (size_t dataRemaining = getdatasizeremaining(m_instance); dataRemaining < sizeBloc) {
				buf.resize(dataRemaining);
				m_instance.read(reinterpret_cast<char *>(buf.data()), dataRemaining * sizeof(char));
				m_instance.close();
				m_isDataSign = false;
				m_name = "";
				m_sizeFich = 0;
			}
			else {
				buf.resize(sizeBloc);
				m_instance.read(reinterpret_cast<char *>(buf.data()), sizeBloc);
			}
		}
		return buf;
	}

	size_t fileRead::gettotalsize() const { return m_isDataSign ? m_sizeFich - m_signFile.size() : m_sizeFich; }



	size_t fileWrite::getsizedatawritten() { return m_isDataSign ? getsizeifstream(m_instance) - m_signFile.size() : getsizeifstream(m_instance); }

	fileWrite::fileWrite() : m_isDataSign(false) {
	}

	fileWrite::fileWrite(const std::string& path, byteArray signFile, bool isDataSign) : m_isDataSign(isDataSign), m_name(path), m_signFile(signFile) {
		m_instance.open(m_name, std::ios::binary | std::ios::out);
		if (isvalid()) {
			if (m_isDataSign) {
				m_instance.write(reinterpret_cast<char *>(m_signFile.data()), m_signFile.size());
			}
			return;
		}
		m_name = "";
		m_isDataSign = false;
	}

	bool fileWrite::open(const std::string& path, bool isDataSign) {
		m_isDataSign = isDataSign;
		m_name = path;
		m_instance.open(m_name, std::ios::binary | std::ios::out);
		if (isvalid()) {
			if (m_isDataSign) {
				m_instance.write(reinterpret_cast<char *>(m_signFile.data()), m_signFile.size());
			}
			return true;
		}
		m_isDataSign = false;
		m_name = "";
		return false;
	}

	void fileWrite::write(byteArray data) {
		if (isvalid())
			m_instance.write(reinterpret_cast<char *>(data.data()), data.size());
	}

}

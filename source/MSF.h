#pragma once
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>


inline size_t getsizeifstream(std::ofstream& instance) {
	size_t buf = static_cast<size_t>(instance.tellp());
	instance.seekp(0, std::ios::end);
	size_t sizeFlux = static_cast<size_t>(instance.tellp());
	instance.seekp(buf);
	return sizeFlux;
}

inline size_t getdatasizeremaining(std::ofstream& instance) {
	size_t buf = static_cast<size_t>(instance.tellp());
	instance.seekp(0, std::ios::end);
	size_t sizeFlux = static_cast<size_t>(instance.tellp()) - buf;
	instance.seekp(buf);
	return sizeFlux;
}

inline size_t getsizeifstream(std::ifstream& instance) {
	size_t buf = static_cast<size_t>(instance.tellg());
	instance.seekg(0, std::ios::end);
	size_t sizeFlux = static_cast<size_t>(instance.tellg());
	instance.seekg(buf);
	return sizeFlux;
}

inline size_t getdatasizeremaining(std::ifstream& instance) {
	size_t buf = static_cast<size_t>(instance.tellg());
	instance.seekg(0, std::ios::end);
	size_t sizeFlux = static_cast<size_t>(instance.tellg()) - buf;
	instance.seekg(buf);
	return sizeFlux;
}

namespace MSF {

	using byteArray = std::vector<uint8_t>;
	extern const byteArray signExample;

	class fileRead {

		std::ifstream m_instance;
		byteArray m_signFile;
		std::string m_name;
		bool m_isDataSign = false;
		size_t m_sizeFich = 0;

	public:

		fileRead();
		fileRead(const std::string& path, byteArray signFi = signExample);
		bool open(const std::string& path);
		byteArray getsignfile() { return m_signFile; }
		void setsignfile(byteArray signFile) { m_signFile = signFile; }
		bool isvalid() { return !m_instance.fail(); }
		explicit operator bool() { return isvalid(); }
		bool isdatasign() const { return m_isDataSign; }
		void close() { m_instance.close(); }
		std::string getname() const { return m_name; }
		size_t gettotalsize() const;
		size_t getremainingsize() { return getdatasizeremaining(m_instance); }
		void statut() {
			std::cout << std::boolalpha;
			std::cout << "isDataSign : " << m_isDataSign << std::endl
				<< "isValid : " << isvalid() << std::endl
				<< "totalSize : " << gettotalsize() << std::endl
				<< "remainingSize : " << getremainingsize() << std::endl
				<< "Name : " << m_name << std::endl;
		}
		byteArray getbloc(size_t sizeBloc = 1024 * 1024 * 5);

	};

	class fileWrite {

		std::ofstream m_instance;
		byteArray m_signFile;
		std::string m_name;
		bool m_isDataSign = false;

	public:

		fileWrite();
		fileWrite(const std::string& path, byteArray signFile = signExample, bool isDataSign = false);
		byteArray getsignfile() { return m_signFile; }
		void setsignfile(byteArray signFile) { m_signFile = signFile; }
		bool open(const std::string& path, bool isDataSign = false);
		void close() { m_instance.close(); m_isDataSign = false; m_name = ""; }
		size_t getsizedatawritten();
		bool isdatasign() { return m_isDataSign; }
		bool isvalid() { return !m_instance.fail(); }
		explicit operator bool() { return isvalid(); }
		void write(byteArray data);
		void statut() {
			std::cout << std::boolalpha;
			std::cout << "isDataSign : " << m_isDataSign << std::endl
				<< "isValid : " << isvalid() << std::endl
				<< "totalSize : " << getsizedatawritten() << std::endl
				<< "Name : " << m_name << std::endl;
		}

	};

}

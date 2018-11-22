/**
* Project GyvrIni
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _GYVRINI_INIFILE_H
#define _GYVRINI_INIFILE_H

#include "GyvrIni/API/Export.h"

#include <string>
#include <unordered_map>

namespace GyvrIni::Core
{
	/**
	* The IniFile class represents a file .ini that stores a set of attributes/values that can get read and written
	*/
	class API_GYVRINI IniFile final
	{
	public:
		IniFile(const std::string& p_filePath);

	private:
		std::unordered_map<std::string, std::string> m_data;
	};
}

#endif // _GYVRINI_INIFILE_H
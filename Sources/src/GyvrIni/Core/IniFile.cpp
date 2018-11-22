/**
* Project GyvrIni
* @author Adrien Givry
* @version 1.0
*/

#include "GyvrIni/Core/IniFile.h"

GyvrIni::Core::IniFile::IniFile(const std::string & p_filePath)
{
	m_data.insert(std::make_pair<std::string, std::string>("", ""));
}

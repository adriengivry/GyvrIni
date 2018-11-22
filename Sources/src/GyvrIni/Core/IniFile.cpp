/**
* Project GyvrIni
* @author Adrien Givry
* @version 1.0
*/

#include "GyvrIni/Core/IniFile.h"

#include <filesystem>
#include <fstream>

GyvrIni::Core::IniFile::IniFile(const std::string& p_filePath) : m_filePath(p_filePath)
{
	Load();
}

void GyvrIni::Core::IniFile::Reload()
{
	RemoveAll();
	Load();
}

bool GyvrIni::Core::IniFile::Remove(const std::string & p_key)
{
	if (IsKeyExisting(p_key))
	{
		m_data.erase(p_key);
		return true;
	}

	return false;
}

void GyvrIni::Core::IniFile::RemoveAll()
{
	m_data.clear();
}

bool GyvrIni::Core::IniFile::IsKeyExisting(const std::string& p_key) const
{
	return m_data.find(p_key) != m_data.end();
}

void GyvrIni::Core::IniFile::RegisterPair(const std::string& p_key, const std::string& p_value)
{
	RegisterPair(std::make_pair(p_key, p_value));
}

void GyvrIni::Core::IniFile::RegisterPair(const AttributePair& p_pair)
{
	m_data.insert(p_pair);
}

std::vector<std::string> GyvrIni::Core::IniFile::GetFormattedContent() const
{
	std::vector<std::string> result;

	for (const auto&[key, value] : m_data)
		result.push_back(key + "=" + value);

	return result;
}

void GyvrIni::Core::IniFile::Load()
{
	std::fstream iniFile;
	iniFile.open(m_filePath);

	if (iniFile.is_open())
	{
		std::string currentLine;

		while (std::getline(iniFile, currentLine))
		{
			if (IsValidLine(currentLine))
			{
				currentLine.erase(std::remove_if(currentLine.begin(), currentLine.end(), isspace), currentLine.end());
				RegisterPair(ExtractKeyAndValue(currentLine));
			}
		}

		iniFile.close();
	}
}

void GyvrIni::Core::IniFile::Rewrite() const
{
	std::ofstream outfile;
	outfile.open(m_filePath, std::ios_base::trunc);

	if (outfile.is_open())
	{
		for (const auto&[key, value] : m_data)
			outfile << key << "=" << value << std::endl;
	}

	outfile.close();
}

std::pair<std::string, std::string> GyvrIni::Core::IniFile::ExtractKeyAndValue(const std::string& p_line) const
{
	std::string key;
	std::string value;

	std::string* currentBuffer = &key;

	for (auto& c : p_line)
	{
		if (c == '=')
			currentBuffer = &value;
		else
			currentBuffer->push_back(c);
	}

	return std::make_pair(key, value);
}

bool GyvrIni::Core::IniFile::IsValidLine(const std::string & p_attributeLine) const
{
	if (p_attributeLine.size() == 0)
		return false;
	
	if (p_attributeLine[0] == '#' || p_attributeLine[0] == ';' || p_attributeLine[0] == '[')
		return false;
	
	if (std::count(p_attributeLine.begin(), p_attributeLine.end(), '=') != 1)
		return false;

	return true;
}

bool GyvrIni::Core::IniFile::StringToBoolean(const std::string & p_value) const
{
	return (p_value == "1" || p_value == "T" || p_value == "t" || p_value == "True" || p_value == "true");
}

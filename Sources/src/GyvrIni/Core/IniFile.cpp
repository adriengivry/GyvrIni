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
	Clear();
	Load();
}

void GyvrIni::Core::IniFile::SaveChanges()
{
	// TODO: WORK IN PROGRESS (Add() not saved yet)

	std::vector<std::string> rawContent;

	GetFileRawContent(rawContent);

	for (std::string& line : rawContent)
	{
		auto[key, value] = ExtractKeyAndValue(line);
		if (IsKeyExisting(key))
			line = key + "=" + m_data[key];
	}

	std::ofstream outfile;
	outfile.open(m_filePath, std::ios_base::trunc);

	if (outfile.is_open())
		for (const std::string& line : rawContent)
			outfile << line << std::endl;

	outfile.close();
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

bool GyvrIni::Core::IniFile::IsKeyExisting(const std::string& p_key)
{
	return m_data.find(p_key) != m_data.end();
}

void GyvrIni::Core::IniFile::RegisterPair(const std::pair<std::string, std::string>& p_pair)
{
	m_data.insert(p_pair);
}

void GyvrIni::Core::IniFile::RegisterPair(const std::string& p_key, const std::string& p_value)
{
	RegisterPair(std::make_pair(p_key, p_value));
}

void GyvrIni::Core::IniFile::Load()
{
	std::fstream iniFile;
	iniFile.open(m_filePath);

	if (iniFile.is_open())
	{
		std::string currentLine;

		while (std::getline(iniFile, currentLine))
			if (IsValidLine(currentLine))
				RegisterPair(ExtractKeyAndValue(currentLine));

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

void GyvrIni::Core::IniFile::Clear()
{
	m_data.clear();
}

void GyvrIni::Core::IniFile::GetFileRawContent(std::vector<std::string>& p_out)
{
	std::fstream iniFile;
	iniFile.open(m_filePath);

	if (iniFile.is_open())
	{
		std::string currentLine;

		while (std::getline(iniFile, currentLine))
			p_out.push_back(currentLine);

		iniFile.close();
	}
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
	
	if (p_attributeLine[0] == '#')
		return false;
	
	if (std::count(p_attributeLine.begin(), p_attributeLine.end(), '=') != 1)
		return false;

	return true;
}

bool GyvrIni::Core::IniFile::StringToBoolean(const std::string & p_value) const
{
	return (p_value == "1" || p_value == "T" || p_value == "t" || p_value == "True" || p_value == "true");
}

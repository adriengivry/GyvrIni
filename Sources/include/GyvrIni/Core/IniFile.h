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
#include <type_traits>

namespace GyvrIni::Core
{
	/**
	* The IniFile class represents a file .ini that stores a set of attributes/values that can get read and written
	*/
	class API_GYVRINI IniFile final
	{
	public:
		/**
		* Create an IniFile by parsing the given file path and extracting key/values pairs for future usage
		* @param p_filePath
		*/
		IniFile(const std::string& p_filePath);

		/**
		* Overwrite the content of the current data by reloading the file
		*/
		void Reload();

		/**
		* Save changes made to the data to the associated file (Filepath given at construction).
		* The effect is similar to Rewrite() but only affect modified lines and preserve comments (Any comment on a modified line will get deleted).
		* This method takes more time to process than the 'destructive' Rewrite()
		*/
		void SaveChanges();

		/**
		* Rewrite the entiere .ini file with the current values. This operation is destructive and can't be undone.
		* Any comment in your .ini file will get destroyed. This method is faster than SaveChanges() because
		* it doesn't have to rewrite comments and ignore consecutive line breaks
		*/
		void Rewrite() const;

		/**
		* Return the value attached to the given key
		* If the key doesn't exist, a default value is returned (0, false, "NULL")
		* @param p_key
		*/
		template<typename T>
		T Get(const std::string& p_key);

		/**
		* Set a new value to the given key (Not applied to the real file untill Rewrite() or Save() is called)
		* @param p_key
		* @param p_value
		*/
		template<typename T>
		bool Set(const std::string& p_key, const T& p_value);
		
		/**
		* Add a new key/value to the IniFile object (Not applied to the real file untill Rewrite() or Save() is called)
		* @param p_key
		* @param p_value
		*/
		template<typename T>
		bool Add(const std::string& p_key, const T& p_value);

		/**
		* Remove a key/value pair identified by the given key (Not applied to the real file untill Rewrite() or Save() is called)
		* @param p_key
		*/
		bool Remove(const std::string& p_key);

		/**
		* Verify if the given key exists
		* @param p_key
		*/
		bool IsKeyExisting(const std::string& p_key);

	private:
		void RegisterPair(const std::string& p_key, const std::string& p_value);
		void RegisterPair(const std::pair<std::string, std::string>& p_pair);

		void Load();
		void Clear();

		void GetFileRawContent(std::vector<std::string>& p_out);
		std::pair<std::string, std::string> ExtractKeyAndValue(const std::string& p_attributeLine) const;
		bool IsValidLine(const std::string& p_attributeLine) const;
		bool StringToBoolean(const std::string& p_value) const;

	private:
		std::string m_filePath;
		std::unordered_map<std::string, std::string> m_data;
	};
}

#include "IniFile.inl"

#endif // _GYVRINI_INIFILE_H
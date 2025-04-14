#pragma once
#include<string>
#include<locale>
#include<codecvt>
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
static std::wstring StringtoWString(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>>m_convert;
	return m_convert.from_bytes(str);
}
static std::string WStringtoString(const std::wstring& wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>>m_convert;
	return m_convert.to_bytes(wstr);
}

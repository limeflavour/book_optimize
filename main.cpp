#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include "opencv2/opencv.hpp"

#include <windows.h>

using namespace std;
using namespace boost;

std::string remove_punctuation(std::string title);
std::string string_To_UTF8(const std::string& str);
std::string UTF8_To_string(const std::string& str);

std::string UTF8_To_string(const std::string& str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];    //一定要加1，不然会出现尾巴
	memset(pwBuf, 0, nwLen * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);
	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string strRet = pBuf;

	delete[]pBuf;
	delete[]pwBuf;
	pBuf = NULL;
	pwBuf = NULL;

	return strRet;
}

std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}
std::string remove_punctuation(std::string title)
{
	//title = UTF8_To_string(title);
	std::vector<std::string> v;
	boost::cmatch what;
	bool matched;
	std::string new_title;
	boost::regex regex_expr = boost::regex("°|…|\\.|。|，|、|,|-|:|：|~|“|”|\\]|\\[|’|‘|，|：|；|;|】|【");
	matched = boost::regex_search(title.c_str(), what, regex_expr);
	if (matched)
	{
		cout << "标题中有标点" << title << endl;
		cout << what << endl;
		boost::split_regex(v, title, regex_expr);
		for (auto it = v.begin(); it != v.end(); it++)
		{
			if (*it != "" && *it != " ")
			{
				new_title += *it;
			}
		}
		return new_title;
	}
	else
	{
		return title;
	}

}
int main()
{
	string test = "【测，，，，量   标志   与,管。理】";
	boost::replace_all(test, " ", "");
	string result = remove_punctuation(test);
	cout << result << endl;
	cout << CV_VERSION << endl;
	system("pause");
    return 0;
}
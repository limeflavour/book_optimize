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
	std::shared_ptr<wchar_t> pwBuf(new wchar_t[nwLen + 1]);    //一定要加1，不然会出现尾巴
	memset(pwBuf.get(), 0, nwLen * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf.get(), nwLen);
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf.get(), -1, NULL, NULL, NULL, NULL);
	std::unique_ptr<char>pBuf(new char[nLen + 1]);
	memset(pBuf.get(), 0, nLen + 1);
	WideCharToMultiByte(CP_ACP, 0, pwBuf.get(), nwLen, pBuf.get(), nLen, NULL, NULL);

	std::string strRet = pBuf.get();

	//delete[]pBuf;
	//delete[]pwBuf;
	//pBuf = nullptr;
	//pwBuf = nullptr;

	return strRet;
}

std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	std::unique_ptr<wchar_t> pwBuf(new wchar_t[nwLen + 1]);//一定要加1，不然会出现尾巴
	ZeroMemory(pwBuf.get(), nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf.get(), nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf.get(), -1, NULL, NULL, NULL, NULL);

	std::unique_ptr<char> pBuf(new char[nLen + 1]);
	ZeroMemory(pBuf.get(), nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf.get(), nwLen, pBuf.get(), nLen, NULL, NULL);

	std::string retStr(pBuf.get());

	//delete[]pwBuf;
	//delete[]pBuf;

	//pwBuf = nullptr;
	//pBuf = nullptr;

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
		for (const auto& item : v)
		{
			if (item != "" && item != " ")
			{
				new_title += item;
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

	cv::Mat img1 = cv::imread("D:\\test\\0679.jpg");
	cv::resize(img1, img1, cv::Size(img1.cols * 0.3, img1.rows * 0.3));
	cv::imshow("text", img1);

	cv::waitKey(0);
    return 0;
}
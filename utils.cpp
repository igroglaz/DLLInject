#include "utils.hpp"

using namespace std;

/*
    utils::TrimLeft, utils::TrimRight, utils::Trim: �������� ���������� ������� � ������ ������ (TrimLeft), � ����� (TrimRight)
        ��� � ���, � ��� (Trim).

    ���������� ���������� ������.

    what: ���������� ������
    callback: �������, ������������ ���������� �������. ��. IsWhitespace
*/
string TrimLeft(const string& what, bool (callback)(char))
{
    string ret = what;
    for(string::iterator i = ret.begin(); i != ret.end(); ++i)
    {
        if(callback((*i)))
            continue;
        ret.erase(ret.begin(), i);
        return ret;
    }
    return "";
}

string TrimRight(const string& what, bool (callback)(char))
{
    string ret = what;
    for(string::reverse_iterator i = ret.rbegin(); i != ret.rend(); ++i)
    {
        if(callback((*i)))
            continue;
        ret.erase(i.base(), ret.end());
        return ret;
    }
    return "";
}

string Trim(const string& what, bool (callback)(char))
{
    return TrimRight(TrimLeft(what, callback));
}

/*
    utils::IsWhitespace: ��������������� ������� ��� Trim*

    ���������� true, ���� ������ �������� �������� � ��� ����� ��������.

    what: ����������� ������.
*/
bool IsWhitespace(char what)
{
    switch((unsigned char)what)
    {
        case ' ':
        case '\r':
        case '\n':
        case '\t':
        case 0xFF:
            return true;
        default:
            return false;
    }
}

/*
    utils::ToLower, utils::ToUpper: �������������� ������ � ������� ��� ������ �������.

    ���������� ��������������� ������.

    what: ����������������� ������.
*/
string ToLower(const string& what)
{
    string ret = what;
    for(string::iterator i = ret.begin(); i != ret.end(); ++i)
        (*i) = tolower((*i));
    return ret;
}

/*
    utils::Basename: ������� ���� � �����, ������� ������ ��� ��������.

    ������������ ��������: ���������� ������.

    filename: ������ �������� �����.
*/
string Basename(const string& filename)
{
    string ret = FixSlashes(filename);
    uint32_t where = ret.find_last_of('/');
    if(where == string::npos) return ret;
    ret.erase(0, where+1);
    return ret;
}

/*
    utils::FixSlashes: ������� ���� � ����� POSIX-����������� (�.�. � ������������� ������� ������ backslash, ������������� � DOS/Windows)

    ������������ ��������: ������������ ������.

    filename: ������ �������� �����.
*/
string FixSlashes(const string& filename)
{
    string ret = filename;
    for(string::iterator i = ret.begin(); i != ret.end(); ++i)
        if((*i) == '\\') (*i) = '/';
    return ret;
}

/*
    utils::TruncateSlashes: ������� ������������� ����� (����. main//graphics/mainmenu//menu_.bmp).

    ���������� ������������ ������.

    filename: ������ �������� �����.
*/
string TruncateSlashes(const string& filename)
{
    string ret = filename;
    char lastchar = 0;
    char thischar = 0;
    for(string::iterator i = ret.begin(); i != ret.end(); ++i)
    {
        thischar = (*i);
        if((thischar == '/' || thischar == '\\') &&
           (lastchar == '/' || lastchar == '\\'))
        {
            ret.erase(i);
            i--;
        }
        lastchar = thischar;
    }
    return ret;
}

unsigned long StrToInt(const string& what)
{
	unsigned int retval;
	sscanf(what.c_str(), "%u", &retval);
	return retval;
}

unsigned long HexToInt(const string& what2)
{
	unsigned int retval;
	string what = what2;
	if(what.find("0x") == 0)
	    what.erase(0, 2);
	sscanf(what.c_str(), "%X", &retval);
	return retval;
}

bool CheckInt(const string& what)
{
	for(size_t i = 0; i < what.length(); i++)
		if(what[i] < 0x30 || 0x39 < what[i]) return false;
	return true;
}

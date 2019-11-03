#include "utils.hpp"

#include <cstdarg>
#include <cstdio>
#include <ctime>

using namespace std;

/*
    utils::Format: �������, ����������� sprintf(), �� ��� STL �����.

    ���������� ����������������� STL ������.

    format: ������
    ...: ��������� ��� �������
*/
std::string Format(const string& format, ...)
{
    char* line = NULL;
    try
    {
        va_list list;
        va_start(list, format);
        size_t linesize = (vsnprintf(NULL, 0, format.c_str(), list) + 1);
        line = new char[linesize + 1];
        if(!line) return "";
        line[linesize] = 0;
        vsnprintf(line, linesize, format.c_str(), list);
        va_end(list);

        std::string sline(line);
        delete[] line;

        return sline;
    }
    catch(...)
    {
        if(line) delete[] line;
        return "";
    }
}

/*
    utils::Explode: ������� ��� ��������� ������ �� ���������.

    ���������� ������ �� ��������� ��������.

    what: ����������� ������
    separator: �����������
*/
vector<string> Explode(const string& what, const string& separator)
{
    string curstr;
    vector<string> retval;
    for(size_t i = 0; i < what.length(); i++)
    {
        if(what.find(separator, i) == i)
        {
            retval.push_back(curstr);
            curstr.assign("");
            i += separator.length()-1;
            continue;
        }

        curstr += what[i];
    }
    retval.push_back(curstr);
    return retval;
}

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

string ToUpper(const string& what)
{
    string ret = what;
    for(string::iterator i = ret.begin(); i != ret.end(); ++i)
        (*i) = toupper((*i));
    return ret;
}

#include <fstream>

/*
    utils::FileExists: �������� �� ������������� �����.

    ���������� true, ���� ���� ����������.

    filename: �������� ������������ �����.
*/
bool FileExists(const string& filename)
{
    ifstream f_temp;
    f_temp.open(filename.c_str(), ios::in | ios::binary);
    if(!f_temp.is_open()) return false;
    f_temp.close();
    return true;
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

/*
    utils::Directory::Open: ��������� �����, � ������� ����� ������������� �����.

    ���������� true ��� �������� �������� �����.

    what: �������� �����.
*/
bool Directory::Open(const string& what)
{
    this->Close();
    this->directory = opendir(what.c_str());
    if(!this->directory) return false;
    return true;
}

/*
    utils::Directory::Read: ��������� ��������� ���� �� �����.

    ������������ ��������: true ���� ��������, false � ��������� ������.

    where: ���������, ���� ����� �������� ������ � �����.
*/
bool Directory::Read(DirectoryEntry& where)
{
    if(!this->directory) return false;
    struct dirent* dp = readdir(this->directory);
    if(!dp) return false;
    if(dp->d_name[0] == '.') return this->Read(where);
    where.name.assign(dp->d_name);
    return true;
}

/*
    utils::Directory::Close: ������� �����.
*/
void Directory::Close()
{
    if(this->directory) closedir(this->directory);
    this->directory = NULL;
}

// �� ������, ����������, ��������
Directory::~Directory()
{
    this->Close();
}

Directory::Directory()
{
    this->directory = NULL;
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

double StrToFloat(const string& what)
{
	float retval;
	sscanf(what.c_str(), "%f", &retval);
	return (double)retval;
}

bool CheckInt(const string& what)
{
	for(size_t i = 0; i < what.length(); i++)
		if(what[i] < 0x30 || 0x39 < what[i]) return false;
	return true;
}

bool CheckFloat(const string& what)
{
	for(size_t i = 0; i < what.length(); i++)
		if((what[i] < 0x30 || 0x39 < what[i]) && what[i] != '.') return false;
	return true;
}

bool CheckHex(const string& what)
{
	for(size_t i = 0; i < what.length(); i++)
		if((what[i] < 0x30 || 0x39 < what[i]) && !(what[i] >= 'A' && what[i] <= 'F') && !(what[i] >= 'a' && what[i] <= 'f')) return false;
	return true;
}

bool CheckBool(const string& what)
{
    string wh2 = ToLower(Trim(what));
    if(wh2 == "true" || wh2 == "false" || wh2 == "yes" || wh2 == "no" || wh2 == "y" || wh2 == "n" || wh2 == "0" || wh2 == "1")
        return true;
    return false;
}

bool StrToBool(const string& what)
{
	string cr = Trim(ToLower(what));
	if(cr == "yes" || cr == "true" || cr == "1" || cr == "y")
		return true;
	return false;
}

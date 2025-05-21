#include "parse.hpp"

#include <fstream>

static int
clamp (int val, int min, int max) {
    return std::min(max, std::max(min, val));
}


// Достает из строки первое попавшееся слово.
static std::string
getWord (const std::string &s)
{
    size_t begin = 0;
    while (begin < s.size() and (not std::isalpha(s[begin])))
        ++begin;
    if (begin >= s.size())
        throw ErrorParse();

    size_t end = begin;
    while (end < s.size() and std::isalpha(s[end]))
        ++end;

    return s.substr(begin, end - begin);
}


// Достает из строки первое попавшееся положительное число.
static int
getNum (const std::string &s) 
{
    size_t begin = 0;
    while (begin < s.size() and (not std::isdigit(s[begin])))
        ++begin;
    if (begin >= s.size())
        throw ErrorParse();

    size_t end = begin;
    while (end < s.size() and std::isdigit(s[end]))
        ++end;

    int res = 0;
    for (size_t i = begin; i < end; ++i)
        res = 10 * res + (s[i] - '0');
    return res;
}


static std::vector<std::string>
readLines (const std::string &fileName)
{
    std::vector<std::string> res;
    std::fstream file;
    std::string line;
    file.open(fileName.c_str(), std::ios::in);
    if (not file.is_open())
        throw(ErrorOpenFile());
    while (std::getline(file, line))
        res.push_back(line);
    file.close();
    return res;
}


GameParameter::GameParameter (const std::string &_name, int _val, int _minVal, int _maxVal)
{
    name   = _name;
    val    = clamp(_val, _minVal, _maxVal);
    minVal = _minVal;
    maxVal = _maxVal;
}


void
Parser::addDefaultParameter (std::string name, int val, int minVal, int maxVal) {
    defaultParams.push_back(GameParameter(name, val, minVal, maxVal));
}

std::map<std::string, int>
Parser::getDefaultParameters () const
{
    std::map<std::string, int> res;
    for (auto const &param: defaultParams)
        res[param.getName()] = param.getVal();
    return res;
}

void
Parser::writeFile (const std::string &fileName, const std::map<std::string, int> &params) const
{
    std::fstream file;
    file.open(fileName.c_str(), std::ios::out);
    if (not file.is_open())
        throw(ErrorOpenFile());

    for (const auto &p: defaultParams)
        file << p.getName() << " " << params.at(p.getName()) << std::endl;

    file << std::endl;
    file << "Ограничения:" << std::endl;
    for (const auto &param: defaultParams)
    {
        file << param.getMinVal();
        file << " <= ";
        file << param.getName();
        file << " <= ";
        file << param.getMaxVal();
        file << std::endl;
    }

    file.close();
}

std::map<std::string, int>
Parser::readFile (const std::string &fileName) const
{
    std::map<std::string, int> res;

    auto lines = readLines(fileName);
    for (size_t i = 0; i < defaultParams.size() and i < lines.size(); ++i)
    {
        auto name = getWord(lines[i]);
        auto val  = getNum(lines[i]);
        if (name != defaultParams[i].getName())
            throw ErrorParse();
        res[name] = clamp(
            val,
            defaultParams[i].getMinVal(),
            defaultParams[i].getMaxVal());
    }
    if (res.size() != defaultParams.size())
        throw ErrorParse();

    return res;
}

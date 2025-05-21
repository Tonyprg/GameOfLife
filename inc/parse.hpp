#ifndef PARSE_HPP
#define PARSE_HPP

#include <string>
#include <vector>
#include <map>

class ErrorOpenFile {};
class ErrorParse {};

class GameParameter
{
    private:

        std::string name;
        int val;
        int minVal;
        int maxVal;

    public:

        GameParameter (const std::string &_name, int _val, int _minVal, int _maxVal);
        virtual ~GameParameter () {}

        std::string
        getName () const {
            return name;
        }

        int
        getVal () const {
            return val;
        }

        int
        getMinVal () const {
            return minVal;
        }

        int
        getMaxVal () const {
            return maxVal;
        }
};

class Parser
{
    private:

        std::vector<GameParameter> defaultParams;

    public:

        void
        addDefaultParameter (std::string name, int val, int minVal, int maxVal);

        std::map<std::string, int>
        getDefaultParameters () const;

        void
        writeFile (const std::string &fileName, const std::map<std::string, int> &params) const;

        std::map<std::string, int>
        readFile (const std::string &fileName) const;
};

#endif

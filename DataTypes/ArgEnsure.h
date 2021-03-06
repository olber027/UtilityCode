//
// Created by molberding on 11/10/2017.
//

#ifndef UTILITYCODE_ARGENSURE_H
#define UTILITYCODE_ARGENSURE_H

#include "Regex.h"
#include "SmartString.h"
#include <cstdlib>
#include <map>
#include <vector>

namespace Utilities
{
    class Argument
    {
    protected:
        SmartString shortOpt;
        SmartString longOpt;
        bool required;

        template <typename T, typename U>
        Argument(const T& shortopt, const U& longopt, const bool isRequired)
            : shortOpt(shortopt), longOpt(longopt), required(isRequired) {}

    public:
        virtual bool isValid(const char*) const = 0;

        virtual SmartString expectedInput() const = 0;

        const SmartString& getShortOpt() { return shortOpt; }

        const SmartString& getLongOpt() { return longOpt; }

        bool isRequired() { return required; }
    };

    class StringArgument : public Argument
    {
    private:
        SmartString acceptedPattern;

    public:
        template <typename T, typename U, typename V>
        StringArgument(const T& shortopt, const U& longopt, const V& pattern, const bool& isRequired)
            : Argument(shortopt, longopt, isRequired), acceptedPattern(pattern)
        {}

        template <typename T, typename U>
        StringArgument(const T& shortopt, const U& pattern)
            : Argument(shortopt, "", false), acceptedPattern(pattern)
        {}

        bool isValid(const char* value) const override
        {
            regex::Regex re(acceptedPattern);
            regex::Match<SmartString> match = re.match<SmartString>(value);
            return match.getPatternIndex() == 0;
        }

        SmartString expectedInput() const override
        {
            SmartString result = shortOpt;
            if(!longOpt.isEmpty())
            {
                result << ", " << longOpt << " : ";
            }
            result << "Expected an argument that matches the pattern: ";
            result << acceptedPattern << "\n";
            return result;
        }
    };

    class IntegerArgument : public Argument
    {
    public:
        template <typename T, typename U>
        IntegerArgument(const T& shortopt, const U& longopt, const bool isRequired)
            : Argument(shortopt, longopt, isRequired)
        {}

        template <typename T>
        IntegerArgument(const T& shortopt, const bool isRequired)
            : Argument(shortopt, "", isRequired)
        {}

        template <typename T>
        explicit IntegerArgument(const T& shortopt)
            : Argument(shortopt, "", false)
        {}

        bool isValid(const char* value) const override
        {
            regex::Regex re("-?[0-9]+");
            regex::Match<SmartString> match = re.match<SmartString>(value);
            return match.getPatternIndex() == 0;
        }

        SmartString expectedInput() const override
        {
            SmartString result = shortOpt;
            if(!longOpt.isEmpty())
            {
                result << ", " << longOpt << " : ";
            }
            result << "Expected argument in the form of an Integer.\n";
            return result;
        }
    };

    class DecimalArgument : public Argument
    {
    public:
        template <typename T, typename U>
        DecimalArgument(const T& shortopt, const U& longopt, const bool isRequired)
            : Argument(shortopt, longopt, isRequired)
        {}

        template <typename T>
        DecimalArgument(const T& shortopt, const bool isRequired)
            : Argument(shortopt, "", isRequired)
        {}

        template <typename T>
        explicit DecimalArgument(const T& shortopt)
            : Argument(shortopt, "", false)
        {}

        bool isValid(const char* value) const override
        {
            double val;
            return SmartString::tryConvert(value, val);
        }

        SmartString expectedInput() const override
        {
            SmartString result = shortOpt;
            if(!longOpt.isEmpty())
            {
                result << ", " << longOpt << " : ";
            }
            result << "Expected argument in the form of a decimal number.\n";
            return result;
        }
    };

    class IntegerRangeArgument : public Argument
    {
    private:
        int min, max;

    public:
        template <typename T, typename U>
        IntegerRangeArgument(const T& shortopt, const U& longopt, const bool isRequired, const int low, const int high)
            : Argument(shortopt, longopt, isRequired), min(low), max(high)
        {}

        template <typename T>
        IntegerRangeArgument(const T& shortopt, const int low, const int high)
            : Argument(shortopt, "", false), min(low), max(high)
        {}

        bool isValid(const char* value) const override
        {
            int intVal;
            if(!SmartString::tryConvert(value, intVal))
            {
                return false;
            }

            return intVal >= min && intVal <= max;
        }

        SmartString expectedInput() const override
        {
            SmartString result = shortOpt;
            if(!longOpt.isEmpty())
            {
                result << ", " << longOpt << " : ";
            }
            result << "Expected an integer in the range";
            result << " [" << min << ", " << max << "]\n";
            return result;
        }
    };

    class DecimalRangeArgument : public Argument
    {
    private:
        double min, max;

    public:
        template <typename T, typename U>
        DecimalRangeArgument(const T& shortopt, const U& longopt, const bool isRequired, const double low, const double high)
            : Argument(shortopt, longopt, isRequired), min(low), max(high)
        {}

        template <typename T>
        DecimalRangeArgument(const T& shortopt, const double low, const double high)
            : Argument(shortopt, "", false), min(low), max(high)
        {}

        bool isValid(const char* value) const override
        {
            double val;
            if(!SmartString::tryConvert(value, val))
            {
                return false;
            }

            return val >= min && val <= max;
        }

        SmartString expectedInput() const override
        {
            SmartString result = shortOpt;
            if(!longOpt.isEmpty())
            {
                result << ", " << longOpt << " : ";
            }
            result << "Expected an number in the range";
            result << " [" << min << ", " << max << "]\n";
            return result;
        }
    };

    class FlagArgument : public Argument
    {
    public:
        template <typename T, typename U>
        FlagArgument(const T& shortopt, const U& longopt, const bool isRequired)
            : Argument(shortopt, longopt, isRequired)
        {}

        template <typename T>
        FlagArgument(const T& shortopt, const bool isRequired)
            : Argument(shortopt, "", isRequired)
        {}

        template <typename T>
        explicit FlagArgument(const T& shortopt)
            : Argument(shortopt, "", false)
        {}

        bool isValid(const char* value) const override
        {
            return value == nullptr;
        }

        SmartString expectedInput() const override
        {
            SmartString result = shortOpt;
            if(!longOpt.isEmpty())
            {
                result << ", " << longOpt << " : ";
            }
            result << "Flag argument was given a value unexpectedly.\n";
            return result;
        }
    };

    class ArgEnsure
    {
    private:
        std::vector<Argument*> arguments;

        template <typename T>
        bool isOption(const T& opt) const
        {
            regex::Regex re("-[A-Za-z_-]+");
            regex::Match<SmartString> match = re.match<SmartString>(opt);
            return match.getPatternIndex() >= 0;
        }

    public:
        ArgEnsure() : arguments(std::vector<Argument*>()) {}

        ~ArgEnsure()
        {
            for(auto& arg : arguments)
            {
                delete arg;
            }
        }

        void addArgument(Argument* arg)
        {
            arguments.push_back(arg);
        }

        std::map<Argument*, SmartString> validateArguments(const int argc, char** argv) const
        {
            std::map<SmartString, char*> argumentMap;
            std::map<Argument*, SmartString> invalidArguments;

            // map the options to their values.
            // e.g. foo -v 3 --no-warnings
            // the option -v would have the value of 3,
            // and no-warnings would be assumed to be a flag
            for(int i = 1; i < argc; i++)
            {
                if(isOption(argv[i]))
                {
                    argumentMap[argv[i]] = nullptr;
                }
                else
                {
                    argumentMap[argv[i - 1]] = argv[i];
                }
            }

            for(int i = 0; i < arguments.size(); i++)
            {
                Argument* arg      = arguments[i];
                char* value        = {'\0'};
                bool argumentFound = false;

                if(argumentMap.count(arg->getShortOpt()) > 0)
                {
                    value         = argumentMap[arg->getShortOpt()];
                    argumentFound = true;
                }
                else if(argumentMap.count(arg->getLongOpt()) > 0)
                {
                    value         = argumentMap[arg->getLongOpt()];
                    argumentFound = true;
                }

                if((argumentFound && !arg->isValid(value)) ||
                   (!argumentFound && arg->isRequired()))
                {
                    invalidArguments[arg] = SmartString(value);
                }
            }

            return invalidArguments;
        }
    };
}// namespace Utilities

#endif//UTILITYCODE_ARGENSURE_H

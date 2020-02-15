//
// Created by molberding on 9/18/2017.
//

#ifndef UTILITYCODE_SMARTSTRINGTESTDRIVER_H
#define UTILITYCODE_SMARTSTRINGTESTDRIVER_H

#include "../DataTypes/SmartString.h"
#include "TestDriver.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace smart_string;

class SmartStringTestDriver : public TestDriver {
private:

public:
    SmartStringTestDriver() {
        init("Smart String");
    };

    void testConstructors() {
        SmartString defaultConstructor;
        assert(0, defaultConstructor.length());
        SmartString charStarConstructor("charStarConstructor");
        assert(std::string("charStarConstructor"), charStarConstructor.str());
        SmartString charConstructor('c');
        assert('c', charConstructor[0]);
        std::string var = "stringConstructor";
        SmartString stringConstructor(var);
        assert(var, stringConstructor.str());
        SmartString fillConstructor(5, 'f');
        assert(std::string("fffff"), fillConstructor.str());
        int count = 0;
        char* tempFill = fillConstructor.c_str();
        while(tempFill[count++] != '\0') { }
        assert(6, count);
        delete tempFill;
        SmartString copyConstructor = fillConstructor;
        assert(copyConstructor.str(), fillConstructor.str());
        copyConstructor = stringConstructor;
        assert(copyConstructor.str(), stringConstructor.str());
        fillConstructor = "operator=";
        assert(std::string("operator="), fillConstructor.str());
        charConstructor = var;
        assert(var, charConstructor.str());

        std::stringstream stream;
        stream << "this is some text";
        SmartString temp = stream;
        SmartString otherTemp(stream);
        assert(std::string("this is some text"), temp.str());
        assert(std::string("this is some text"), otherTemp.str());
    }

    void testAppendPrepend() {
        SmartString temp;
        temp.append('1');
        assert(std::string("1"), temp.str());
        temp.append("23");
        assert(std::string("123"), temp.str());
        std::string var = "456";
        temp.append(var);
        assert(std::string("123456"), temp.str());
        SmartString smart = "789";
        temp.append(smart);
        assert(std::string("123456789"), temp.str());
        temp.prepend('0');
        assert(std::string("0123456789"), temp.str());
        temp.prepend("789");
        assert(std::string("7890123456789"), temp.str());
        temp.prepend(var);
        assert(std::string("4567890123456789"), temp.str());
        smart = "123";
        temp.prepend(smart);
        assert(std::string("1234567890123456789"), temp.str());

        temp = "";
        temp.append(1.0, 1);
        assert(std::string("1.0"), temp.str());
        temp.append(", ").append(-2.123456, 6);
        assert(std::string("1.0, -2.123456"), temp.str());
        temp.prepend(", ").prepend(-105.12345);
        assert(std::string("-105.12345, 1.0, -2.123456"), temp.str());

        temp = "";
        temp.append(2.5);
        assert(std::string("2.5"), temp.str());
        temp += 2.5200000;
        assert(std::string("2.52.52"), temp.str());

        temp = "";
        temp.append(2.54234235235);
        assert(std::string("2.54234"), temp.str());

        temp.setPrecision(2);
        temp = "";
        temp += 2.5467;
        assert(std::string("2.54"), temp.str());

        temp = "";
        temp += 2.00;
        assert(std::string("2.0"), temp.str());
    }

    void testOperators() {
        SmartString temp = "1";
        temp << "234" << "5";
        assert(std::string("12345"), temp.str());
        temp << '6';
        assert(std::string("123456"), temp.str());
        std::string var = "789";
        temp << var;
        assert(std::string("123456789"), temp.str());
        temp = "";
        temp << 1.23456;
        assert(std::string("1.23456"), temp.str());
        SmartString test = " + 2";
        temp << test;
        assert(std::string("1.23456 + 2"), temp.str());

        temp = "2";
        temp.prepend('1').append("345").prepend("0");
        assert(std::string("012345"), temp.str());

        temp = "1";
        temp += "2";
        assert(std::string("12"), temp.str());

        temp = temp + "3" + '4';
        assert(std::string("1234"), temp.str());

        temp = "5" + temp;
        assert(std::string("51234"), temp.str());

        temp = var + temp;
        assert(std::string("78951234"), temp.str());

        assert(true, temp.contains("123"));
        assert(4, temp.findSubstring("123"));

        temp = "123";
        std::string str = "123";
        SmartString smartStr = "123";
        assert(true, (temp == smartStr));
        assert(true, (smartStr == temp));
        assert(true, (temp == str));
        assert(true, (str == temp));
        assert(true, (temp == "123"));
        assert(true, ("123" == temp));

        assert(false, (temp != smartStr));
        assert(false, (smartStr != temp));
        assert(false, (temp != str));
        assert(false, (str != temp));
        assert(false, (temp != "123"));
        assert(false, ("123" != temp));

        temp = "1";

        assert(true, (temp == '1'));
        assert(false, (temp != '1'));

        temp = "a";
        smartStr = "b";
        assert(true, (temp < smartStr));
        assert(false, (temp > smartStr));
        assert(true, (temp <= smartStr));
        assert(false, (temp >= smartStr));

        temp = "c";
        assert(true, ("a" < temp));
        assert(true, ("d" > temp));
        assert(true, ("c" >= temp));
        assert(true, ("c" <= temp));

        temp = "bad";
        temp[0] = 'c';
        assert(std::string("cad"), temp.str());
        temp[2] = 't';
        assert(std::string("cat"), temp.str());
    }

    void testReplaceAndFormat() {
        SmartString temp = "78951234";
        temp.replace("789", "123");
        assert(std::string("12351234"), temp.str());

        temp.replaceAll("123", "x");
        assert(std::string("x5x4"), temp.str());

        temp = "1";
        temp << 2345;
        assert(std::string("12345"), temp.str());

        SmartString formatString = "{0} {1} {2} {0}";
        formatString.format("a", "b", "c");
        assert(std::string("a b c a"), formatString.str());

        std::string str = (std::string) temp;
        assert(std::string("12345"), str);

        char* charStr = (char*) temp;
        assert(temp.str(), std::string(charStr));

        formatString = "{0} {1} {2} {0}";
        str = formatString.getFormatted<std::string>("a", "b", "c");
        assert(std::string("a b c a"), str);
        charStr = formatString.getFormatted<char *>("a", "b", "c");
        assert(std::string("a b c a"), std::string(charStr));
        temp = formatString.getFormatted<SmartString>("a", "b", "c");
        assert(std::string("a b c a"), temp.str());

        str = SmartString::format<std::string>(formatString, "a", "b", "c");
        assert(std::string("a b c a"), str);
        charStr = SmartString::format<char *>("{0} {1} {2} {0}", "a", "b", "c");
        assert(std::string("a b c a"), std::string(charStr));
        str = "{0} {1} {2} {0}";
        temp = SmartString::format<SmartString>(str, "a", "b", "c");
        assert(std::string("a b c a"), temp.str());
    }

    void testRemove() {
        SmartString temp = "123411";
        temp.remove("23");
        assert(std::string("1411"), temp.str());
        temp.removeAll("1");
        assert(std::string("4"), temp.str());
        temp = "123456";
        temp.remove(0, 0);
        assert(std::string("23456"), temp.str());
        temp.remove(0, 2);
        assert(std::string("56"), temp.str());
        temp.remove(1,1);
        assert(std::string("5"), temp.str());

        temp = " \t1234 \n";
        assert(std::string("1234 \n"), temp.lstrip().str());
        assert(std::string("1234"), temp.rstrip().str());
        temp = " \t1234 \n";
        assert(std::string("1234"), temp.strip().str());

        temp = "aaa1234vvvv";
        assert(std::string("1234vvvv"), temp.lstrip("a").str());
        assert(std::string("1234"), temp.rstrip("v").str());

        temp = "12121";
        assert(std::string("2121"), temp.lstrip("1").str());
        assert(std::string("212"), temp.rstrip("1").str());
        assert(std::string("1"), temp.strip("2").str());
    }

    void testSubstrings() {
        SmartString temp("1212121");
        assert(4, temp.count("1"));
        assert(3, temp.count("12"));
        assert(0, temp.count("3"));
        temp = "12314516";
        assert(std::string("1"), temp.getSubstring<std::string>(0,0));
        std::vector<SmartString> list = temp.split<SmartString>("1");
        assert(4, (int) list.size());
        assert(std::string(""), list[0].str());
        assert(std::string("23"), list[1].str());
        assert(std::string("45"), list[2].str());
        assert(std::string("6"), list[3].str());
        temp = "this is a multi-line piece of text.\n";
        temp.append("it's way longer than it has any right to be.\n");
        temp.append("....that's what she said.\n");
        list = temp.split<SmartString>("\n");
        assert(3, (int) list.size());
        assert(std::string("this is a multi-line piece of text."), list[0].str());
        assert(std::string("it's way longer than it has any right to be."), list[1].str());
        assert(std::string("....that's what she said."), list[2].str());
        std::string tempStr = SmartString::join<std::string>(list, "\n");
        assert(std::string("this is a multi-line piece of text.\nit's way longer than it has any right to be.\n....that's what she said."), tempStr);

        auto array = new SmartString[3];
        for(int i = 0; i < 3; i++) {
            array[i] = list[i];
        }
        SmartString result = SmartString::join<SmartString>(array, 3, "\n");
        assert(std::string("this is a multi-line piece of text.\nit's way longer than it has any right to be.\n....that's what she said."), result.str());
        //                  012345678910
        assert(10, result.findSubstring("multi"));
        assert(2, result.findSubstring("is"));
        assert(5, result.findSubstring(4, "is"));
        assert(-1, result.findSubstring("foo"));
        assert(-1, result.findSubstring(5000, "foo"));
        assert(-1, result.findSubstring(-600, "foo"));
    }

    void testMiscFunctions() {
        SmartString temp(".';,!@#$%aBcDeFgHiJkLmNoPqRsTuVwXyZ0123456789");
        temp.toUpper();
        assert(std::string(".';,!@#$%ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"), temp.str());
        temp.toLower();
        assert(std::string(".';,!@#$%abcdefghijklmnopqrstuvwxyz0123456789"), temp.str());

        double val;
        bool result = SmartString::tryConvert("-1.56", val);
        assert(true, result);
        assert(-1.56, val);

        result = SmartString::tryConvert("123.56", val);
        assert(true, result);
        assert(123.56, val);

        result = SmartString::tryConvert("-1.56a", val);
        assert(false, result);
        assert(123.56, val);

        result = SmartString::tryConvert("-1", val);
        assert(true, result);
        assert(-1.0, val);

        result = SmartString::tryConvert("12345", val);
        assert(true, result);
        assert(12345.0, val);

        result = SmartString::tryConvert("0001000000.000001000", val);
        assert(true, result);
        assert(1000000.000001, val);

        int intVal;
        result = SmartString::tryConvert("123", intVal);
        assert(true, result);
        assert(123, intVal);

        float floatVal;
        result = SmartString::tryConvert("12.3", floatVal);
        assert(true, result);
        assert((float) 12.3, floatVal);

        val = SmartString::convert<double>("12.5");
        assert((double) 12.5, val);

        floatVal = SmartString::convert<float>("12.45");
        assert((float) 12.45, floatVal);

        intVal = SmartString::convert<int>("123");
        assert(123, intVal);

        std::string errorMessage;
        try {
            val = SmartString::convert<double>("123a");
        } catch (std::invalid_argument& e) {
            errorMessage = e.what();
        }
        assert(std::string("source string was not a valid number"), errorMessage);
    }

    void testFunctionPassing() {
        SmartString test = "Get Basic String";
        SmartString result = getBasicString();
        assert(test, result);
        test = "Get Reference String";
        result = getReferenceString();
        assert(test, result);
        test = "Pass Basic String";
        passBasicString(test);
        test = "Pass Reference String";
        passReferenceString(test);
    }

    SmartString getBasicString() {
        SmartString result = "Get Basic String";
        return result;
    }

    SmartString& getReferenceString() {
        auto result = new SmartString();
        *result = "Get Reference String";
        return *result;
    }

    void passBasicString(SmartString test) {
        assert(SmartString("Pass Basic String"), test);
    }

    void passReferenceString(SmartString& test) {
        assert(SmartString("Pass Reference String"), test);
    }

    void run() override {
        testConstructors();
        testAppendPrepend();
        testOperators();
        testReplaceAndFormat();
        testRemove();
        testSubstrings();
        testMiscFunctions();
        testFunctionPassing();
    }
};
#endif //UTILITYCODE_SMARTSTRINGTESTDRIVER_H

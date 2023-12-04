//
// Created by olber on 2/20/2021.
//
#include "SmartStringTestDriver.h"

SmartStringTestDriver::SmartStringTestDriver() : TestDriver("Smart String") {}

void SmartStringTestDriver::testConstructors()
{
    SmartString defaultConstructor;
    assert(0, defaultConstructor.length());
    SmartString charStarConstructor("charStarConstructor");
    assert("charStarConstructor", charStarConstructor);
    SmartString charConstructor('c');
    assert('c', charConstructor[0]);
    std::string var = "stringConstructor";
    SmartString stringConstructor(var);
    assert(var, stringConstructor);
    SmartString fillConstructor(5, 'f');
    assert("fffff", fillConstructor);
    int count      = 0;
    char* tempFill = fillConstructor.c_str();
    while(tempFill[count++] != '\0') {}
    assert(6, count);
    delete tempFill;
    SmartString copyConstructor = fillConstructor;
    assert(copyConstructor, fillConstructor);
    copyConstructor = stringConstructor;
    assert(copyConstructor, stringConstructor);
    fillConstructor = "operator=";
    assert("operator=", fillConstructor);
    charConstructor = var;
    assert(var, charConstructor);

    std::stringstream stream;
    stream << "this is some text";
    SmartString temp = stream;
    SmartString otherTemp(stream);
    assert("this is some text", temp);
    assert("this is some text", otherTemp);
}

void SmartStringTestDriver::testAppendPrepend()
{
    SmartString temp;
    temp.append('1');
    assert("1", temp);
    temp.append("23");
    assert("123", temp);
    std::string var = "456";
    temp.append(var);
    assert("123456", temp);
    SmartString smart = "789";
    temp.append(smart);
    assert("123456789", temp);
    temp.prepend('0');
    assert("0123456789", temp);
    temp.prepend("789");
    assert("7890123456789", temp);
    temp.prepend(var);
    assert("4567890123456789", temp);
    smart = "123";
    temp.prepend(smart);
    assert("1234567890123456789", temp);

    temp = "";
    temp.append(1.0, 1);
    assert("1.0", temp);
    temp.append(", ").append(-2.123456, 6);
    assert("1.0, -2.123456", temp);
    temp.prepend(", ").prepend(-105.12345);
    assert("-105.12345, 1.0, -2.123456", temp);

    temp = "";
    temp.append(2.5);
    assert("2.5", temp);
    temp += 2.5200000;
    assert("2.52.52", temp);

    temp = "";
    temp.append(2.54234235235);
    assert("2.54234", temp);

    temp = "";
    temp.setPrecision(2);
    temp += 2.5467;
    assert("2.54", temp);

    temp = "";
    temp += 2.00;
    assert("2.0", temp);
}

void SmartStringTestDriver::testOperators()
{
    SmartString temp = "1";
    temp << "234"
         << "5";
    assert("12345", temp);
    temp << '6';
    assert("123456", temp);
    std::string var = "789";
    temp << var;
    assert("123456789", temp);
    temp = "";
    temp << 1.23456;
    assert("1.23456", temp);
    SmartString test = " + 2";
    temp << test;
    assert("1.23456 + 2", temp);

    temp = "2";
    temp.prepend('1').append("345").prepend("0");
    assert("012345", temp);

    temp = "1";
    temp += "2";
    assert("12", temp);

    temp = temp + "3" + '4';
    assert("1234", temp);

    temp = "5" + temp;
    assert("51234", temp);

    temp = var + temp;
    assert("78951234", temp);

    assert(true, temp.contains("123"));
    assert(4, temp.findSubstring("123"));

    temp                 = "123";
    std::string str      = "123";
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

    temp     = "a";
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

    temp    = "bad";
    temp[0] = 'c';
    assert("cad", temp);
    temp[2] = 't';
    assert("cat", temp);
}

void SmartStringTestDriver::testReplaceAndFormat()
{
    SmartString temp = "78951234";
    temp.replace("789", "123");
    assert("12351234", temp);

    temp.replaceAll("123", "x");
    assert("x5x4", temp);

    temp = "1";
    temp << 2345;
    assert("12345", temp);

    SmartString formatString = "{0} {1} {2} {0}";
    formatString.format("a", "b", "c");
    assert("a b c a", formatString);

    std::string str = (std::string) temp;
    assert("12345", str);

    char* charStr = (char*) temp;
    assert(charStr, temp);

    formatString = "{0} {1} {2} {0}";
    str          = formatString.getFormatted<std::string>("a", "b", "c");
    assert(std::string("a b c a"), str);
    charStr = formatString.getFormatted<char*>("a", "b", "c");
    assert("a b c a", std::string(charStr));
    temp = formatString.getFormatted<SmartString>("a", "b", "c");
    assert("a b c a", temp);

    str = SmartString::format<std::string>(formatString, "a", "b", "c");
    assert("a b c a", str);
    charStr = SmartString::format<char*>("{0} {1} {2} {0}", "a", "b", "c");
    assert("a b c a", std::string(charStr));
    str  = "{0} {1} {2} {0}";
    temp = SmartString::format<SmartString>(str, "a", "b", "c");
    assert("a b c a", temp);
}

void SmartStringTestDriver::testRemove()
{
    SmartString temp = "123411";
    temp.remove("23");
    assert("1411", temp);
    temp.removeAll("1");
    assert("4", temp);
    temp = "123456";
    temp.remove(0, 0);
    assert("23456", temp);
    temp.remove(0, 2);
    assert("56", temp);
    temp.remove(1, 1);
    assert("5", temp);

    temp = " \t1234 \n";
    assert("1234 \n", temp.lstrip());
    assert("1234", temp.rstrip());
    temp = " \t1234 \n";
    assert("1234", temp.strip());

    temp = "aaa1234vvvv";
    assert("1234vvvv", temp.lstrip("a"));
    assert("1234", temp.rstrip("v"));

    temp = "12121";
    assert("2121", temp.lstrip("1"));
    assert("212", temp.rstrip("1"));
    assert("1", temp.strip("2"));
}

void SmartStringTestDriver::testSubstrings()
{
    SmartString temp("1212121");
    assert(4, temp.count("1"));
    assert(3, temp.count("12"));
    assert(0, temp.count("3"));
    temp = "12314516";
    assert("1", temp.getSubstring<std::string>(0, 0));
    std::vector<SmartString> list = temp.split<SmartString>("1");
    assert(4, list.size());
    assert("", list[0]);
    assert("23", list[1]);
    assert("45", list[2]);
    assert("6", list[3]);
    temp = "this is a multi-line piece of text.\n";
    temp.append("it's way longer than it has any right to be.\n");
    temp.append("....that's what she said.\n");
    list = temp.split<SmartString>("\n");
    assert(3, list.size());
    assert("this is a multi-line piece of text.", list[0]);
    assert("it's way longer than it has any right to be.", list[1]);
    assert("....that's what she said.", list[2]);
    auto tempStr = SmartString::join<std::string>(list, "\n");
    assert("this is a multi-line piece of text.\nit's way longer than it has any right to be.\n....that's what she said.", tempStr);

    auto array = new SmartString[3];
    for(int i = 0; i < 3; i++)
    {
        array[i] = list[i];
    }
    auto result = SmartString::join<SmartString>(array, 3, "\n");
    assert("this is a multi-line piece of text.\nit's way longer than it has any right to be.\n....that's what she said.", result);
    //      012345678910
    assert(10, result.findSubstring("multi"));
    assert(2, result.findSubstring("is"));
    assert(5, result.findSubstring(4, "is"));
    assert(-1, result.findSubstring("foo"));
    assert(-1, result.findSubstring(5000, "foo"));
    assert(-1, result.findSubstring(-600, "foo"));
}

void SmartStringTestDriver::testMiscFunctions()
{
    SmartString temp(".';,!@#$%aBcDeFgHiJkLmNoPqRsTuVwXyZ0123456789");
    temp.toUpper();
    assert(".';,!@#$%ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", temp);
    temp.toLower();
    assert(".';,!@#$%abcdefghijklmnopqrstuvwxyz0123456789", temp);

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
    assert(12.5, val);

    floatVal = SmartString::convert<float>("12.45");
    assert((float) 12.45, floatVal);

    intVal = SmartString::convert<int>("123");
    assert(123, intVal);

    std::string errorMessage;
    try
    {
        val = SmartString::convert<double>("123a");
    }
    catch(std::invalid_argument& e)
    {
        errorMessage = e.what();
    }
    assert("The given string could not be parsed into a valid number: 123a", errorMessage);
}

void SmartStringTestDriver::testFunctionPassing()
{
    SmartString test   = "Get Basic String";
    SmartString result = getBasicString();
    assert(test, result);
    test   = "Get Reference String";
    result = getReferenceString();
    assert(test, result);
    test = "Pass Basic String";
    passBasicString(test);
    test = "Pass Reference String";
    passReferenceString(test);
}

SmartString SmartStringTestDriver::getBasicString()
{
    SmartString result = "Get Basic String";
    return result;
}

SmartString& SmartStringTestDriver::getReferenceString()
{
    auto result = new SmartString();
    *result     = "Get Reference String";
    return *result;
}

void SmartStringTestDriver::passBasicString(SmartString test)
{
    assert(SmartString("Pass Basic String"), test);
}

void SmartStringTestDriver::passReferenceString(SmartString& test)
{
    assert(SmartString("Pass Reference String"), test);
}

void SmartStringTestDriver::run()
{
    testConstructors();
    testAppendPrepend();
    testOperators();
    testReplaceAndFormat();
    testRemove();
    testSubstrings();
    testMiscFunctions();
    testFunctionPassing();
}